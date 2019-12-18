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
typedef  unsigned int const u32 ;
struct uniphier_pinctrl_priv {int /*<<< orphan*/  regmap; } ;
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
struct pin_desc {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int const,...) ; 
 struct pin_desc* pin_desc_get (struct pinctrl_dev*,unsigned int) ; 
 struct uniphier_pinctrl_priv* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int uniphier_conf_get_drvctrl_data (struct pinctrl_dev*,unsigned int,unsigned int*,unsigned int*,unsigned int*,unsigned int const**) ; 

__attribute__((used)) static int uniphier_conf_pin_drive_set(struct pinctrl_dev *pctldev,
				       unsigned int pin, u32 strength)
{
	struct uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	const struct pin_desc *desc = pin_desc_get(pctldev, pin);
	unsigned int reg, shift, mask, val;
	const unsigned int *strengths;
	int ret;

	ret = uniphier_conf_get_drvctrl_data(pctldev, pin, &reg, &shift,
					     &mask, &strengths);
	if (ret) {
		dev_err(pctldev->dev, "cannot set drive strength for pin %s\n",
			desc->name);
		return ret;
	}

	for (val = 0; val <= mask; val++) {
		if (strengths[val] > strength)
			break;
	}

	if (val == 0) {
		dev_err(pctldev->dev,
			"unsupported drive strength %u mA for pin %s\n",
			strength, desc->name);
		return -EINVAL;
	}

	if (!mask)
		return 0;

	val--;

	return regmap_update_bits(priv->regmap, reg,
				  mask << shift, val << shift);
}