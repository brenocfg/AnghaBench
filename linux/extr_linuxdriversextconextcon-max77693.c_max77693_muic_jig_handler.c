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
typedef  int /*<<< orphan*/  u8 ;
struct max77693_muic_info {int /*<<< orphan*/  edev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EXTCON_JIG ; 
 int /*<<< orphan*/  MAX77693_CONTROL1_SW_OPEN ; 
 int /*<<< orphan*/  MAX77693_CONTROL1_SW_UART ; 
 int /*<<< orphan*/  MAX77693_CONTROL1_SW_USB ; 
#define  MAX77693_MUIC_ADC_FACTORY_MODE_UART_OFF 131 
#define  MAX77693_MUIC_ADC_FACTORY_MODE_UART_ON 130 
#define  MAX77693_MUIC_ADC_FACTORY_MODE_USB_OFF 129 
#define  MAX77693_MUIC_ADC_FACTORY_MODE_USB_ON 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max77693_muic_set_path (struct max77693_muic_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max77693_muic_jig_handler(struct max77693_muic_info *info,
		int cable_type, bool attached)
{
	int ret = 0;
	u8 path = MAX77693_CONTROL1_SW_OPEN;

	dev_info(info->dev,
		"external connector is %s (adc:0x%02x)\n",
		attached ? "attached" : "detached", cable_type);

	switch (cable_type) {
	case MAX77693_MUIC_ADC_FACTORY_MODE_USB_OFF:	/* ADC_JIG_USB_OFF */
	case MAX77693_MUIC_ADC_FACTORY_MODE_USB_ON:	/* ADC_JIG_USB_ON */
		/* PATH:AP_USB */
		path = MAX77693_CONTROL1_SW_USB;
		break;
	case MAX77693_MUIC_ADC_FACTORY_MODE_UART_OFF:	/* ADC_JIG_UART_OFF */
	case MAX77693_MUIC_ADC_FACTORY_MODE_UART_ON:	/* ADC_JIG_UART_ON */
		/* PATH:AP_UART */
		path = MAX77693_CONTROL1_SW_UART;
		break;
	default:
		dev_err(info->dev, "failed to detect %s jig cable\n",
			attached ? "attached" : "detached");
		return -EINVAL;
	}

	ret = max77693_muic_set_path(info, path, attached);
	if (ret < 0)
		return ret;

	extcon_set_state_sync(info->edev, EXTCON_JIG, attached);

	return 0;
}