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
struct rzn1_pinctrl {TYPE_1__* lev1; int /*<<< orphan*/  dev; } ;
struct pinctrl_dev {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
struct TYPE_2__ {int /*<<< orphan*/ * conf; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  LOCK_LEVEL1 ; 
#define  PIN_CONFIG_BIAS_DISABLE 132 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 131 
#define  PIN_CONFIG_BIAS_PULL_DOWN 130 
#define  PIN_CONFIG_BIAS_PULL_UP 129 
#define  PIN_CONFIG_DRIVE_STRENGTH 128 
 int RZN1_FUNC_HIGHZ ; 
 int RZN1_L1_FUNC_MASK ; 
 int RZN1_L1_PIN_DRIVE_STRENGTH ; 
 int RZN1_L1_PIN_DRIVE_STRENGTH_12MA ; 
 int RZN1_L1_PIN_DRIVE_STRENGTH_4MA ; 
 int RZN1_L1_PIN_DRIVE_STRENGTH_6MA ; 
 int RZN1_L1_PIN_DRIVE_STRENGTH_8MA ; 
 int RZN1_L1_PIN_PULL ; 
 int RZN1_L1_PIN_PULL_DOWN ; 
 int RZN1_L1_PIN_PULL_NONE ; 
 int RZN1_L1_PIN_PULL_UP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct rzn1_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rzn1_hw_set_lock (struct rzn1_pinctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rzn1_pinconf_set(struct pinctrl_dev *pctldev, unsigned int pin,
			    unsigned long *configs, unsigned int num_configs)
{
	struct rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param;
	unsigned int i;
	u32 l1, l1_cache;
	u32 drv;
	u32 arg;

	if (pin >= ARRAY_SIZE(ipctl->lev1->conf))
		return -EINVAL;

	l1 = readl(&ipctl->lev1->conf[pin]);
	l1_cache = l1;

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		switch (param) {
		case PIN_CONFIG_BIAS_PULL_UP:
			dev_dbg(ipctl->dev, "set pin %d pull up\n", pin);
			l1 &= ~(0x3 << RZN1_L1_PIN_PULL);
			l1 |= (RZN1_L1_PIN_PULL_UP << RZN1_L1_PIN_PULL);
			break;
		case PIN_CONFIG_BIAS_PULL_DOWN:
			dev_dbg(ipctl->dev, "set pin %d pull down\n", pin);
			l1 &= ~(0x3 << RZN1_L1_PIN_PULL);
			l1 |= (RZN1_L1_PIN_PULL_DOWN << RZN1_L1_PIN_PULL);
			break;
		case PIN_CONFIG_BIAS_DISABLE:
			dev_dbg(ipctl->dev, "set pin %d bias off\n", pin);
			l1 &= ~(0x3 << RZN1_L1_PIN_PULL);
			l1 |= (RZN1_L1_PIN_PULL_NONE << RZN1_L1_PIN_PULL);
			break;
		case PIN_CONFIG_DRIVE_STRENGTH:
			dev_dbg(ipctl->dev, "set pin %d drv %umA\n", pin, arg);
			switch (arg) {
			case 4:
				drv = RZN1_L1_PIN_DRIVE_STRENGTH_4MA;
				break;
			case 6:
				drv = RZN1_L1_PIN_DRIVE_STRENGTH_6MA;
				break;
			case 8:
				drv = RZN1_L1_PIN_DRIVE_STRENGTH_8MA;
				break;
			case 12:
				drv = RZN1_L1_PIN_DRIVE_STRENGTH_12MA;
				break;
			default:
				dev_err(ipctl->dev,
					"Drive strength %umA not supported\n",
					arg);

				return -EINVAL;
			}

			l1 &= ~(0x3 << RZN1_L1_PIN_DRIVE_STRENGTH);
			l1 |= (drv << RZN1_L1_PIN_DRIVE_STRENGTH);
			break;

		case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			dev_dbg(ipctl->dev, "set pin %d High-Z\n", pin);
			l1 &= ~RZN1_L1_FUNC_MASK;
			l1 |= RZN1_FUNC_HIGHZ;
			break;
		default:
			return -ENOTSUPP;
		}
	}

	if (l1 != l1_cache) {
		rzn1_hw_set_lock(ipctl, LOCK_LEVEL1, LOCK_LEVEL1);
		writel(l1, &ipctl->lev1->conf[pin]);
		rzn1_hw_set_lock(ipctl, LOCK_LEVEL1, 0);
	}

	return 0;
}