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
typedef  unsigned int u32 ;
struct pinctrl_dev {int dummy; } ;
struct amd_gpio {TYPE_1__* pdev; int /*<<< orphan*/  lock; scalar_t__ base; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 unsigned int DB_TMR_OUT_MASK ; 
 unsigned int DRV_STRENGTH_SEL_MASK ; 
 unsigned int DRV_STRENGTH_SEL_OFF ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_PULL_DOWN 131 
#define  PIN_CONFIG_BIAS_PULL_UP 130 
#define  PIN_CONFIG_DRIVE_STRENGTH 129 
#define  PIN_CONFIG_INPUT_DEBOUNCE 128 
 unsigned int PULL_DOWN_ENABLE_OFF ; 
 unsigned int PULL_UP_SEL_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 unsigned long pinconf_to_config_packed (int,unsigned int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct amd_gpio* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static int amd_pinconf_get(struct pinctrl_dev *pctldev,
			  unsigned int pin,
			  unsigned long *config)
{
	u32 pin_reg;
	unsigned arg;
	unsigned long flags;
	struct amd_gpio *gpio_dev = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = readl(gpio_dev->base + pin*4);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);
	switch (param) {
	case PIN_CONFIG_INPUT_DEBOUNCE:
		arg = pin_reg & DB_TMR_OUT_MASK;
		break;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		arg = (pin_reg >> PULL_DOWN_ENABLE_OFF) & BIT(0);
		break;

	case PIN_CONFIG_BIAS_PULL_UP:
		arg = (pin_reg >> PULL_UP_SEL_OFF) & (BIT(0) | BIT(1));
		break;

	case PIN_CONFIG_DRIVE_STRENGTH:
		arg = (pin_reg >> DRV_STRENGTH_SEL_OFF) & DRV_STRENGTH_SEL_MASK;
		break;

	default:
		dev_err(&gpio_dev->pdev->dev, "Invalid config param %04x\n",
			param);
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}