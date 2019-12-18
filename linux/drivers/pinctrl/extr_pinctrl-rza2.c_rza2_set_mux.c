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
struct rza2_pinctrl_priv {int /*<<< orphan*/  base; int /*<<< orphan*/  dev; } ;
struct pinctrl_dev {int dummy; } ;
struct group_desc {unsigned int num_pins; int /*<<< orphan*/ * pins; } ;
struct function_desc {unsigned int* data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RZA2_PIN_ID_TO_PIN (int /*<<< orphan*/ ) ; 
 size_t RZA2_PIN_ID_TO_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct rza2_pinctrl_priv* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 struct group_desc* pinctrl_generic_get_group (struct pinctrl_dev*,unsigned int) ; 
 struct function_desc* pinmux_generic_get_function (struct pinctrl_dev*,unsigned int) ; 
 int /*<<< orphan*/ * port_names ; 
 int /*<<< orphan*/  rza2_set_pin_function (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int rza2_set_mux(struct pinctrl_dev *pctldev, unsigned int selector,
			unsigned int group)
{
	struct rza2_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	struct function_desc *func;
	unsigned int i, *psel_val;
	struct group_desc *grp;

	grp = pinctrl_generic_get_group(pctldev, group);
	if (!grp)
		return -EINVAL;

	func = pinmux_generic_get_function(pctldev, selector);
	if (!func)
		return -EINVAL;

	psel_val = func->data;

	for (i = 0; i < grp->num_pins; ++i) {
		dev_dbg(priv->dev, "Setting P%c_%d to PSEL=%d\n",
			port_names[RZA2_PIN_ID_TO_PORT(grp->pins[i])],
			RZA2_PIN_ID_TO_PIN(grp->pins[i]),
			psel_val[i]);
		rza2_set_pin_function(
			priv->base,
			RZA2_PIN_ID_TO_PORT(grp->pins[i]),
			RZA2_PIN_ID_TO_PIN(grp->pins[i]),
			psel_val[i]);
	}

	return 0;
}