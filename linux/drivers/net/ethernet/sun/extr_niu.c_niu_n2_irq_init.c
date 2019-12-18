#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int num_irqs; int /*<<< orphan*/ * irqs; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ archdata; TYPE_3__ dev; } ;
struct niu {int num_ldg; TYPE_1__* ldg; struct platform_device* op; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/ * of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int niu_n2_irq_init(struct niu *np, u8 *ldg_num_map)
{
#ifdef CONFIG_SPARC64
	struct platform_device *op = np->op;
	const u32 *int_prop;
	int i;

	int_prop = of_get_property(op->dev.of_node, "interrupts", NULL);
	if (!int_prop)
		return -ENODEV;

	for (i = 0; i < op->archdata.num_irqs; i++) {
		ldg_num_map[i] = int_prop[i];
		np->ldg[i].irq = op->archdata.irqs[i];
	}

	np->num_ldg = op->archdata.num_irqs;

	return 0;
#else
	return -EINVAL;
#endif
}