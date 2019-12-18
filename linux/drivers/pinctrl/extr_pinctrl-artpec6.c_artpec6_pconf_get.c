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
struct artpec6_pmx {unsigned int num_pins; scalar_t__ base; TYPE_1__* pins; int /*<<< orphan*/  dev; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARTPEC6_PINMUX_DRV_MASK ; 
 unsigned int ARTPEC6_PINMUX_DRV_SHIFT ; 
 unsigned int ARTPEC6_PINMUX_UDC0_MASK ; 
 unsigned int ARTPEC6_PINMUX_UDC1_MASK ; 
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 131 
#define  PIN_CONFIG_BIAS_PULL_DOWN 130 
#define  PIN_CONFIG_BIAS_PULL_UP 129 
#define  PIN_CONFIG_DRIVE_STRENGTH 128 
 unsigned int artpec6_pconf_drive_field_to_mA (unsigned int) ; 
 scalar_t__ artpec6_pmx_reg_offset (unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 unsigned long pinconf_to_config_packed (int,unsigned int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct artpec6_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static int artpec6_pconf_get(struct pinctrl_dev *pctldev, unsigned int pin,
			     unsigned long *config)
{
	struct artpec6_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	unsigned int regval;

	/* Check for valid pin */
	if (pin >= pmx->num_pins) {
		dev_dbg(pmx->dev, "pinconf is not supported for pin %s\n",
			pmx->pins[pin].name);
		return -ENOTSUPP;
	}

	dev_dbg(pmx->dev, "getting configuration for pin %s\n",
		pmx->pins[pin].name);

	/* Read pin register values */
	regval = readl(pmx->base + artpec6_pmx_reg_offset(pin));

	/* If valid, get configuration for parameter */
	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		if (!(regval & ARTPEC6_PINMUX_UDC1_MASK))
			return -EINVAL;
		break;

	case PIN_CONFIG_BIAS_PULL_UP:
	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (regval & ARTPEC6_PINMUX_UDC1_MASK)
			return -EINVAL;

		regval = regval & ARTPEC6_PINMUX_UDC0_MASK;
		if ((param == PIN_CONFIG_BIAS_PULL_UP && !regval) ||
		    (param == PIN_CONFIG_BIAS_PULL_DOWN && regval))
			return -EINVAL;
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		regval = (regval & ARTPEC6_PINMUX_DRV_MASK)
			>> ARTPEC6_PINMUX_DRV_SHIFT;
		regval = artpec6_pconf_drive_field_to_mA(regval);
		*config = pinconf_to_config_packed(param, regval);
		break;
	default:
		return -ENOTSUPP;
	}

	return 0;
}