#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int start; int flags; int end; } ;
struct TYPE_2__ {int /*<<< orphan*/  bits; } ;
struct pnp_irq {int flags; TYPE_1__ map; } ;
struct pnp_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int IORESOURCE_AUTO ; 
 int IORESOURCE_DISABLED ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int IORESOURCE_IRQ_OPTIONAL ; 
 int PNP_IRQ_NR ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,int) ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pnp_add_irq_resource (struct pnp_dev*,int,int) ; 
 scalar_t__ pnp_check_irq (struct pnp_dev*,struct resource*) ; 
 int /*<<< orphan*/  pnp_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 struct resource* pnp_find_resource (struct pnp_dev*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pnp_assign_irq(struct pnp_dev *dev, struct pnp_irq *rule, int idx)
{
	struct resource *res, local_res;
	int i;

	/* IRQ priority: this table is good for i386 */
	static unsigned short xtab[16] = {
		5, 10, 11, 12, 9, 14, 15, 7, 3, 4, 13, 0, 1, 6, 8, 2
	};

	res = pnp_find_resource(dev, rule->flags, IORESOURCE_IRQ, idx);
	if (res) {
		pnp_dbg(&dev->dev, "  irq %d already set to %d flags %#lx\n",
			idx, (int) res->start, res->flags);
		return 0;
	}

	res = &local_res;
	res->flags = rule->flags | IORESOURCE_AUTO;
	res->start = -1;
	res->end = -1;

	if (bitmap_empty(rule->map.bits, PNP_IRQ_NR)) {
		res->flags |= IORESOURCE_DISABLED;
		pnp_dbg(&dev->dev, "  irq %d disabled\n", idx);
		goto __add;
	}

	/* TBD: need check for >16 IRQ */
	res->start = find_next_bit(rule->map.bits, PNP_IRQ_NR, 16);
	if (res->start < PNP_IRQ_NR) {
		res->end = res->start;
		goto __add;
	}
	for (i = 0; i < 16; i++) {
		if (test_bit(xtab[i], rule->map.bits)) {
			res->start = res->end = xtab[i];
			if (pnp_check_irq(dev, res))
				goto __add;
		}
	}

	if (rule->flags & IORESOURCE_IRQ_OPTIONAL) {
		res->start = -1;
		res->end = -1;
		res->flags |= IORESOURCE_DISABLED;
		pnp_dbg(&dev->dev, "  irq %d disabled (optional)\n", idx);
		goto __add;
	}

	pnp_dbg(&dev->dev, "  couldn't assign irq %d\n", idx);
	return -EBUSY;

__add:
	pnp_add_irq_resource(dev, res->start, res->flags);
	return 0;
}