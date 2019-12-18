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
struct pinctrl_dev {int dummy; } ;
struct mtk_pinctrl {char** grp_names; TYPE_1__* soc; } ;
struct TYPE_2__ {unsigned int ngrps; } ;

/* Variables and functions */
 struct mtk_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int mtk_pmx_get_func_groups(struct pinctrl_dev *pctldev,
				   unsigned function,
				   const char * const **groups,
				   unsigned * const num_groups)
{
	struct mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);

	*groups = hw->grp_names;
	*num_groups = hw->soc->ngrps;

	return 0;
}