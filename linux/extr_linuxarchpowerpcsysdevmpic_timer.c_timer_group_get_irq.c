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
typedef  unsigned int u32 ;
struct timer_group_priv {TYPE_1__* timer; int /*<<< orphan*/  idle; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  all_timer ;
struct TYPE_2__ {unsigned int irq; unsigned int num; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int const TIMERS_PER_GROUP ; 
 int /*<<< orphan*/  TIMER_OFFSET (unsigned int) ; 
 unsigned int irq_of_parse_and_map (struct device_node*,unsigned int) ; 
 unsigned int* of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*) ; 

__attribute__((used)) static int timer_group_get_irq(struct device_node *np,
		struct timer_group_priv *priv)
{
	const u32 all_timer[] = { 0, TIMERS_PER_GROUP };
	const u32 *p;
	u32 offset;
	u32 count;

	unsigned int i;
	unsigned int j;
	unsigned int irq_index = 0;
	unsigned int irq;
	int len;

	p = of_get_property(np, "fsl,available-ranges", &len);
	if (p && len % (2 * sizeof(u32)) != 0) {
		pr_err("%pOF: malformed available-ranges property.\n", np);
		return -EINVAL;
	}

	if (!p) {
		p = all_timer;
		len = sizeof(all_timer);
	}

	len /= 2 * sizeof(u32);

	for (i = 0; i < len; i++) {
		offset = p[i * 2];
		count = p[i * 2 + 1];
		for (j = 0; j < count; j++) {
			irq = irq_of_parse_and_map(np, irq_index);
			if (!irq) {
				pr_err("%pOF: irq parse and map failed.\n", np);
				return -EINVAL;
			}

			/* Set timer idle */
			priv->idle |= TIMER_OFFSET((offset + j));
			priv->timer[offset + j].irq = irq;
			priv->timer[offset + j].num = offset + j;
			irq_index++;
		}
	}

	return 0;
}