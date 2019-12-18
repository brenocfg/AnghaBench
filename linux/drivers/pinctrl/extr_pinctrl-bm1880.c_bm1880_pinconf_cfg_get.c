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
struct bm1880_pinctrl {TYPE_1__* pinconf; scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  drv_bits; } ;

/* Variables and functions */
 int BIT (int) ; 
 int BM1880_PINCONF_DRV (unsigned int) ; 
 int BM1880_PINCONF_PULLCTRL (unsigned int) ; 
 int BM1880_PINCONF_PULLDOWN (unsigned int) ; 
 int BM1880_PINCONF_PULLUP (unsigned int) ; 
 int BM1880_PINCONF_SCHMITT (unsigned int) ; 
 int BM1880_PINCONF_SLEW (unsigned int) ; 
 scalar_t__ BM1880_REG_MUX ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 133 
#define  PIN_CONFIG_BIAS_PULL_DOWN 132 
#define  PIN_CONFIG_BIAS_PULL_UP 131 
#define  PIN_CONFIG_DRIVE_STRENGTH 130 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int bm1880_pinconf_drv_get (int /*<<< orphan*/ ,int) ; 
 unsigned long pinconf_to_config_packed (unsigned int,unsigned int) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 
 struct bm1880_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int bm1880_pinconf_cfg_get(struct pinctrl_dev *pctldev,
				  unsigned int pin,
				  unsigned long *config)
{
	struct bm1880_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	unsigned int param = pinconf_to_config_param(*config);
	unsigned int arg = 0;
	u32 regval, offset, bit_offset;
	int ret;

	offset = (pin >> 1) << 2;
	regval = readl_relaxed(pctrl->base + BM1880_REG_MUX + offset);

	switch (param) {
	case PIN_CONFIG_BIAS_PULL_UP:
		bit_offset = BM1880_PINCONF_PULLUP(pin);
		arg = !!(regval & BIT(bit_offset));
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		bit_offset = BM1880_PINCONF_PULLDOWN(pin);
		arg = !!(regval & BIT(bit_offset));
		break;
	case PIN_CONFIG_BIAS_DISABLE:
		bit_offset = BM1880_PINCONF_PULLCTRL(pin);
		arg = !!(regval & BIT(bit_offset));
		break;
	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		bit_offset = BM1880_PINCONF_SCHMITT(pin);
		arg = !!(regval & BIT(bit_offset));
		break;
	case PIN_CONFIG_SLEW_RATE:
		bit_offset = BM1880_PINCONF_SLEW(pin);
		arg = !!(regval & BIT(bit_offset));
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		bit_offset = BM1880_PINCONF_DRV(pin);
		ret = bm1880_pinconf_drv_get(pctrl->pinconf[pin].drv_bits,
					     !!(regval & BIT(bit_offset)));
		if (ret < 0)
			return ret;

		arg = ret;
		break;
	default:
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}