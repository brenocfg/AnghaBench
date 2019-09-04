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
struct max77693_muic_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  edev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_SDP ; 
 int /*<<< orphan*/  EXTCON_DISP_MHL ; 
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 int /*<<< orphan*/  MAX77693_CABLE_GROUP_ADC_GND ; 
 int /*<<< orphan*/  MAX77693_CONTROL1_SW_AUDIO ; 
 int /*<<< orphan*/  MAX77693_CONTROL1_SW_USB ; 
#define  MAX77693_MUIC_GND_AV_CABLE_LOAD 132 
#define  MAX77693_MUIC_GND_MHL 131 
#define  MAX77693_MUIC_GND_MHL_VB 130 
#define  MAX77693_MUIC_GND_USB_HOST 129 
#define  MAX77693_MUIC_GND_USB_HOST_VB 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max77693_muic_get_cable_type (struct max77693_muic_info*,int /*<<< orphan*/ ,int*) ; 
 int max77693_muic_set_path (struct max77693_muic_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max77693_muic_adc_ground_handler(struct max77693_muic_info *info)
{
	int cable_type_gnd;
	int ret = 0;
	bool attached;

	cable_type_gnd = max77693_muic_get_cable_type(info,
				MAX77693_CABLE_GROUP_ADC_GND, &attached);

	switch (cable_type_gnd) {
	case MAX77693_MUIC_GND_USB_HOST:
	case MAX77693_MUIC_GND_USB_HOST_VB:
		/* USB_HOST, PATH: AP_USB */
		ret = max77693_muic_set_path(info, MAX77693_CONTROL1_SW_USB,
						attached);
		if (ret < 0)
			return ret;
		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, attached);
		break;
	case MAX77693_MUIC_GND_AV_CABLE_LOAD:
		/* Audio Video Cable with load, PATH:AUDIO */
		ret = max77693_muic_set_path(info, MAX77693_CONTROL1_SW_AUDIO,
						attached);
		if (ret < 0)
			return ret;
		extcon_set_state_sync(info->edev, EXTCON_USB, attached);
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
					attached);
		break;
	case MAX77693_MUIC_GND_MHL:
	case MAX77693_MUIC_GND_MHL_VB:
		/* MHL or MHL with USB/TA cable */
		extcon_set_state_sync(info->edev, EXTCON_DISP_MHL, attached);
		break;
	default:
		dev_err(info->dev, "failed to detect %s cable of gnd type\n",
			attached ? "attached" : "detached");
		return -EINVAL;
	}

	return 0;
}