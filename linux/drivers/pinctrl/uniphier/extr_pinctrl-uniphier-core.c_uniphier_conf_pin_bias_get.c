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
struct uniphier_pinctrl_priv {int /*<<< orphan*/  regmap; } ;
struct pinctrl_dev {int dummy; } ;
struct pin_desc {int /*<<< orphan*/  drv_data; } ;
typedef  enum uniphier_pin_pull_dir { ____Placeholder_uniphier_pin_pull_dir } uniphier_pin_pull_dir ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
#define  PIN_CONFIG_BIAS_DISABLE 130 
#define  PIN_CONFIG_BIAS_PULL_DOWN 129 
#define  PIN_CONFIG_BIAS_PULL_UP 128 
 unsigned int UNIPHIER_PINCTRL_PUPDCTRL_BASE ; 
 int UNIPHIER_PIN_PULL_DOWN ; 
 int UNIPHIER_PIN_PULL_DOWN_FIXED ; 
 int UNIPHIER_PIN_PULL_NONE ; 
 int UNIPHIER_PIN_PULL_UP ; 
 int UNIPHIER_PIN_PULL_UP_FIXED ; 
 struct pin_desc* pin_desc_get (struct pinctrl_dev*,unsigned int) ; 
 struct uniphier_pinctrl_priv* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 int uniphier_pin_get_pull_dir (int /*<<< orphan*/ ) ; 
 unsigned int uniphier_pin_get_pupdctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_conf_pin_bias_get(struct pinctrl_dev *pctldev,
				      unsigned int pin,
				      enum pin_config_param param)
{
	struct uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	const struct pin_desc *desc = pin_desc_get(pctldev, pin);
	enum uniphier_pin_pull_dir pull_dir =
				uniphier_pin_get_pull_dir(desc->drv_data);
	unsigned int pupdctrl, reg, shift, val;
	unsigned int expected = 1;
	int ret;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		if (pull_dir == UNIPHIER_PIN_PULL_NONE)
			return 0;
		if (pull_dir == UNIPHIER_PIN_PULL_UP_FIXED ||
		    pull_dir == UNIPHIER_PIN_PULL_DOWN_FIXED)
			return -EINVAL;
		expected = 0;
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		if (pull_dir == UNIPHIER_PIN_PULL_UP_FIXED)
			return 0;
		if (pull_dir != UNIPHIER_PIN_PULL_UP)
			return -EINVAL;
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (pull_dir == UNIPHIER_PIN_PULL_DOWN_FIXED)
			return 0;
		if (pull_dir != UNIPHIER_PIN_PULL_DOWN)
			return -EINVAL;
		break;
	default:
		BUG();
	}

	pupdctrl = uniphier_pin_get_pupdctrl(desc->drv_data);

	reg = UNIPHIER_PINCTRL_PUPDCTRL_BASE + pupdctrl / 32 * 4;
	shift = pupdctrl % 32;

	ret = regmap_read(priv->regmap, reg, &val);
	if (ret)
		return ret;

	val = (val >> shift) & 1;

	return (val == expected) ? 0 : -EINVAL;
}