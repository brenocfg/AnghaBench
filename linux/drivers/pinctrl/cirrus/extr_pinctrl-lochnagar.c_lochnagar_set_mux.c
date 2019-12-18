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
struct lochnagar_pin_priv {int /*<<< orphan*/  dev; TYPE_1__* pins; struct lochnagar_group* groups; struct lochnagar_func* funcs; } ;
struct lochnagar_pin {int /*<<< orphan*/  name; } ;
struct lochnagar_group {size_t* pins; int /*<<< orphan*/  name; } ;
struct lochnagar_func {int type; int /*<<< orphan*/  op; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct lochnagar_pin* drv_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LN_FTYPE_AIF 129 
#define  LN_FTYPE_PIN 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lochnagar_aif_set_mux (struct lochnagar_pin_priv*,struct lochnagar_group const*,int /*<<< orphan*/ ) ; 
 int lochnagar_pin_set_mux (struct lochnagar_pin_priv*,struct lochnagar_pin const*,int /*<<< orphan*/ ) ; 
 struct lochnagar_pin_priv* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int lochnagar_set_mux(struct pinctrl_dev *pctldev,
			     unsigned int func_idx, unsigned int group_idx)
{
	struct lochnagar_pin_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	const struct lochnagar_func *func = &priv->funcs[func_idx];
	const struct lochnagar_group *group = &priv->groups[group_idx];
	const struct lochnagar_pin *pin;

	switch (func->type) {
	case LN_FTYPE_AIF:
		dev_dbg(priv->dev, "Set group %s to %s\n",
			group->name, func->name);

		return lochnagar_aif_set_mux(priv, group, func->op);
	case LN_FTYPE_PIN:
		pin = priv->pins[*group->pins].drv_data;

		dev_dbg(priv->dev, "Set pin %s to %s\n", pin->name, func->name);

		return lochnagar_pin_set_mux(priv, pin, func->op);
	default:
		return -EINVAL;
	}
}