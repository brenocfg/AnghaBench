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
typedef  int u32 ;
struct rzn1_pinctrl {TYPE_2__* lev2; TYPE_1__* lev1; } ;
struct pinctrl_dev {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
struct TYPE_4__ {int /*<<< orphan*/ * conf; } ;
struct TYPE_3__ {int /*<<< orphan*/ * conf; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 132 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 131 
#define  PIN_CONFIG_BIAS_PULL_DOWN 130 
#define  PIN_CONFIG_BIAS_PULL_UP 129 
#define  PIN_CONFIG_DRIVE_STRENGTH 128 
 int RZN1_FUNC_HIGHZ ; 
 int RZN1_L1_FUNCTION_L2 ; 
 int RZN1_L1_FUNC_MASK ; 
 int RZN1_L1_PIN_DRIVE_STRENGTH ; 
 int RZN1_L1_PIN_PULL ; 
 int RZN1_L1_PIN_PULL_DOWN ; 
 int RZN1_L1_PIN_PULL_NONE ; 
 int RZN1_L1_PIN_PULL_UP ; 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct rzn1_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rzn1_pinconf_get(struct pinctrl_dev *pctldev, unsigned int pin,
			    unsigned long *config)
{
	struct rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	const u32 reg_drive[4] = { 4, 6, 8, 12 };
	u32 pull, drive, l1mux;
	u32 l1, l2, arg = 0;

	if (pin >= ARRAY_SIZE(ipctl->lev1->conf))
		return -EINVAL;

	l1 = readl(&ipctl->lev1->conf[pin]);

	l1mux = l1 & RZN1_L1_FUNC_MASK;
	pull = (l1 >> RZN1_L1_PIN_PULL) & 0x3;
	drive = (l1 >> RZN1_L1_PIN_DRIVE_STRENGTH) & 0x3;

	switch (param) {
	case PIN_CONFIG_BIAS_PULL_UP:
		if (pull != RZN1_L1_PIN_PULL_UP)
			return -EINVAL;
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (pull != RZN1_L1_PIN_PULL_DOWN)
			return -EINVAL;
		break;
	case PIN_CONFIG_BIAS_DISABLE:
		if (pull != RZN1_L1_PIN_PULL_NONE)
			return -EINVAL;
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		arg = reg_drive[drive];
		break;
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		l2 = readl(&ipctl->lev2->conf[pin]);
		if (l1mux == RZN1_L1_FUNCTION_L2) {
			if (l2 != 0)
				return -EINVAL;
		} else if (l1mux != RZN1_FUNC_HIGHZ) {
			return -EINVAL;
		}
		break;
	default:
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}