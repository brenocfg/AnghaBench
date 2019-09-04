#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timer_group_priv {int flags; void* group_tcr; void* regs; int /*<<< orphan*/  node; int /*<<< orphan*/  lock; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int FSL_GLOBAL_TIMER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MPIC_TIMER_TCR_CLKDIV ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  kfree (struct timer_group_priv*) ; 
 struct timer_group_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 void* of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*) ; 
 int /*<<< orphan*/  setbits32 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int timer_group_get_freq (struct device_node*,struct timer_group_priv*) ; 
 int timer_group_get_irq (struct device_node*,struct timer_group_priv*) ; 
 int /*<<< orphan*/  timer_group_list ; 

__attribute__((used)) static void timer_group_init(struct device_node *np)
{
	struct timer_group_priv *priv;
	unsigned int i = 0;
	int ret;

	priv = kzalloc(sizeof(struct timer_group_priv), GFP_KERNEL);
	if (!priv) {
		pr_err("%pOF: cannot allocate memory for group.\n", np);
		return;
	}

	if (of_device_is_compatible(np, "fsl,mpic-global-timer"))
		priv->flags |= FSL_GLOBAL_TIMER;

	priv->regs = of_iomap(np, i++);
	if (!priv->regs) {
		pr_err("%pOF: cannot ioremap timer register address.\n", np);
		goto out;
	}

	if (priv->flags & FSL_GLOBAL_TIMER) {
		priv->group_tcr = of_iomap(np, i++);
		if (!priv->group_tcr) {
			pr_err("%pOF: cannot ioremap tcr address.\n", np);
			goto out;
		}
	}

	ret = timer_group_get_freq(np, priv);
	if (ret < 0) {
		pr_err("%pOF: cannot get timer frequency.\n", np);
		goto out;
	}

	ret = timer_group_get_irq(np, priv);
	if (ret < 0) {
		pr_err("%pOF: cannot get timer irqs.\n", np);
		goto out;
	}

	spin_lock_init(&priv->lock);

	/* Init FSL timer hardware */
	if (priv->flags & FSL_GLOBAL_TIMER)
		setbits32(priv->group_tcr, MPIC_TIMER_TCR_CLKDIV);

	list_add_tail(&priv->node, &timer_group_list);

	return;

out:
	if (priv->regs)
		iounmap(priv->regs);

	if (priv->group_tcr)
		iounmap(priv->group_tcr);

	kfree(priv);
}