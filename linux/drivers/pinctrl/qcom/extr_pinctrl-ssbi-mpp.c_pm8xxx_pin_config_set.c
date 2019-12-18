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
struct pm8xxx_pin_data {unsigned int pullup; int high_z; int input; int output; int output_value; unsigned int power_source; unsigned int drive_strength; unsigned int dtest; unsigned int amux; unsigned int aout_level; int paired; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct pm8xxx_mpp {int /*<<< orphan*/  dev; TYPE_2__ desc; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_3__ {struct pm8xxx_pin_data* drv_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 137 
#define  PIN_CONFIG_BIAS_PULL_UP 136 
#define  PIN_CONFIG_DRIVE_STRENGTH 135 
#define  PIN_CONFIG_INPUT_ENABLE 134 
#define  PIN_CONFIG_OUTPUT 133 
#define  PIN_CONFIG_POWER_SOURCE 132 
#define  PM8XXX_CONFIG_ALEVEL 131 
#define  PM8XXX_CONFIG_AMUX 130 
#define  PM8XXX_CONFIG_DTEST_SELECTOR 129 
#define  PM8XXX_CONFIG_PAIRED 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int pinconf_to_config_argument (unsigned long) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 
 struct pm8xxx_mpp* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  pm8xxx_mpp_update (struct pm8xxx_mpp*,struct pm8xxx_pin_data*) ; 

__attribute__((used)) static int pm8xxx_pin_config_set(struct pinctrl_dev *pctldev,
				 unsigned int offset,
				 unsigned long *configs,
				 unsigned num_configs)
{
	struct pm8xxx_mpp *pctrl = pinctrl_dev_get_drvdata(pctldev);
	struct pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	unsigned param;
	unsigned arg;
	unsigned i;

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		switch (param) {
		case PIN_CONFIG_BIAS_PULL_UP:
			pin->pullup = arg;
			break;
		case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			pin->high_z = true;
			break;
		case PIN_CONFIG_INPUT_ENABLE:
			pin->input = true;
			break;
		case PIN_CONFIG_OUTPUT:
			pin->output = true;
			pin->output_value = !!arg;
			break;
		case PIN_CONFIG_POWER_SOURCE:
			pin->power_source = arg;
			break;
		case PIN_CONFIG_DRIVE_STRENGTH:
			pin->drive_strength = arg;
			break;
		case PM8XXX_CONFIG_DTEST_SELECTOR:
			pin->dtest = arg;
			break;
		case PM8XXX_CONFIG_AMUX:
			pin->amux = arg;
			break;
		case PM8XXX_CONFIG_ALEVEL:
			pin->aout_level = arg;
			break;
		case PM8XXX_CONFIG_PAIRED:
			pin->paired = !!arg;
			break;
		default:
			dev_err(pctrl->dev,
				"unsupported config parameter: %x\n",
				param);
			return -EINVAL;
		}
	}

	pm8xxx_mpp_update(pctrl, pin);

	return 0;
}