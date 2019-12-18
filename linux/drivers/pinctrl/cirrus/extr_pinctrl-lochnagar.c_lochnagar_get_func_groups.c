#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct lochnagar_pin_priv {TYPE_2__* func_groups; TYPE_1__* funcs; } ;
struct TYPE_4__ {char** groups; unsigned int ngroups; } ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */
 struct lochnagar_pin_priv* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int lochnagar_get_func_groups(struct pinctrl_dev *pctldev,
				     unsigned int func_idx,
				     const char * const **groups,
				     unsigned int * const num_groups)
{
	struct lochnagar_pin_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	int func_type;

	func_type = priv->funcs[func_idx].type;

	*groups = priv->func_groups[func_type].groups;
	*num_groups = priv->func_groups[func_type].ngroups;

	return 0;
}