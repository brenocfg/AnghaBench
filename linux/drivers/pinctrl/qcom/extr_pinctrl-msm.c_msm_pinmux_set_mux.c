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
typedef  int u32 ;
struct pinctrl_dev {int dummy; } ;
struct msm_pingroup {int mux_bit; int nfuncs; unsigned int* funcs; } ;
struct msm_pinctrl {int /*<<< orphan*/  lock; TYPE_1__* soc; } ;
struct TYPE_2__ {struct msm_pingroup* groups; } ;

/* Variables and functions */
 int EINVAL ; 
 int GENMASK (scalar_t__,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int msm_readl_ctl (struct msm_pinctrl*,struct msm_pingroup const*) ; 
 int /*<<< orphan*/  msm_writel_ctl (int,struct msm_pinctrl*,struct msm_pingroup const*) ; 
 scalar_t__ order_base_2 (int) ; 
 struct msm_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int msm_pinmux_set_mux(struct pinctrl_dev *pctldev,
			      unsigned function,
			      unsigned group)
{
	struct msm_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	const struct msm_pingroup *g;
	unsigned long flags;
	u32 val, mask;
	int i;

	g = &pctrl->soc->groups[group];
	mask = GENMASK(g->mux_bit + order_base_2(g->nfuncs) - 1, g->mux_bit);

	for (i = 0; i < g->nfuncs; i++) {
		if (g->funcs[i] == function)
			break;
	}

	if (WARN_ON(i == g->nfuncs))
		return -EINVAL;

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	val = msm_readl_ctl(pctrl, g);
	val &= ~mask;
	val |= i << g->mux_bit;
	msm_writel_ctl(val, pctrl, g);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	return 0;
}