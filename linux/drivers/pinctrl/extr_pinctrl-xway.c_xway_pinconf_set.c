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
typedef  int /*<<< orphan*/  u32 ;
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
struct ltq_pinmux_info {int /*<<< orphan*/ * membase; } ;
typedef  enum ltq_pinconf_param { ____Placeholder_ltq_pinconf_param } ltq_pinconf_param ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  GPIO3_OD ; 
 int /*<<< orphan*/  GPIO3_PUDEN ; 
 int /*<<< orphan*/  GPIO3_PUDSEL ; 
 int /*<<< orphan*/  GPIO_DIR (unsigned int) ; 
 int /*<<< orphan*/  GPIO_OD (unsigned int) ; 
 int /*<<< orphan*/  GPIO_PUDEN (unsigned int) ; 
 int /*<<< orphan*/  GPIO_PUDSEL (unsigned int) ; 
#define  LTQ_PINCONF_PARAM_OPEN_DRAIN 130 
#define  LTQ_PINCONF_PARAM_OUTPUT 129 
#define  LTQ_PINCONF_PARAM_PULL 128 
 int LTQ_PINCONF_UNPACK_ARG (unsigned long) ; 
 int LTQ_PINCONF_UNPACK_PARAM (unsigned long) ; 
 int PORT (unsigned int) ; 
 int PORT3 ; 
 int /*<<< orphan*/  PORT_PIN (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpio_clearbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_setbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ltq_pinmux_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int xway_pinconf_set(struct pinctrl_dev *pctldev,
				unsigned pin,
				unsigned long *configs,
				unsigned num_configs)
{
	struct ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctldev);
	enum ltq_pinconf_param param;
	int arg;
	int port = PORT(pin);
	u32 reg;
	int i;

	for (i = 0; i < num_configs; i++) {
		param = LTQ_PINCONF_UNPACK_PARAM(configs[i]);
		arg = LTQ_PINCONF_UNPACK_ARG(configs[i]);

		switch (param) {
		case LTQ_PINCONF_PARAM_OPEN_DRAIN:
			if (port == PORT3)
				reg = GPIO3_OD;
			else
				reg = GPIO_OD(pin);
			if (arg == 0)
				gpio_setbit(info->membase[0],
					reg,
					PORT_PIN(pin));
			else
				gpio_clearbit(info->membase[0],
					reg,
					PORT_PIN(pin));
			break;

		case LTQ_PINCONF_PARAM_PULL:
			if (port == PORT3)
				reg = GPIO3_PUDEN;
			else
				reg = GPIO_PUDEN(pin);
			if (arg == 0) {
				gpio_clearbit(info->membase[0],
					reg,
					PORT_PIN(pin));
				break;
			}
			gpio_setbit(info->membase[0], reg, PORT_PIN(pin));

			if (port == PORT3)
				reg = GPIO3_PUDSEL;
			else
				reg = GPIO_PUDSEL(pin);
			if (arg == 1)
				gpio_clearbit(info->membase[0],
					reg,
					PORT_PIN(pin));
			else if (arg == 2)
				gpio_setbit(info->membase[0],
					reg,
					PORT_PIN(pin));
			else
				dev_err(pctldev->dev,
					"Invalid pull value %d\n", arg);
			break;

		case LTQ_PINCONF_PARAM_OUTPUT:
			reg = GPIO_DIR(pin);
			if (arg == 0)
				gpio_clearbit(info->membase[0],
					reg,
					PORT_PIN(pin));
			else
				gpio_setbit(info->membase[0],
					reg,
					PORT_PIN(pin));
			break;

		default:
			dev_err(pctldev->dev,
				"Invalid config param %04x\n", param);
			return -ENOTSUPP;
		}
	} /* for each config */

	return 0;
}