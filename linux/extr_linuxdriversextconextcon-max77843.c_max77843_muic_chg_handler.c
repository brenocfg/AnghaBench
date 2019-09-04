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
struct max77843_muic_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  edev; int /*<<< orphan*/  prev_chg_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_CDP ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_DCP ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_FAST ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_SDP ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_SLOW ; 
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  MAX77843_CABLE_GROUP_ADC_GND ; 
 int /*<<< orphan*/  MAX77843_CABLE_GROUP_CHG ; 
#define  MAX77843_MUIC_CHG_DEDICATED 135 
#define  MAX77843_MUIC_CHG_DOCK 134 
#define  MAX77843_MUIC_CHG_DOWNSTREAM 133 
#define  MAX77843_MUIC_CHG_GND 132 
#define  MAX77843_MUIC_CHG_NONE 131 
#define  MAX77843_MUIC_CHG_SPECIAL_1A 130 
#define  MAX77843_MUIC_CHG_SPECIAL_500MA 129 
#define  MAX77843_MUIC_CHG_USB 128 
 int /*<<< orphan*/  MAX77843_MUIC_CONTROL1_SW_OPEN ; 
 int /*<<< orphan*/  MAX77843_MUIC_CONTROL1_SW_USB ; 
 int MAX77843_MUIC_GND_MHL ; 
 int MAX77843_MUIC_GND_MHL_VB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max77843_muic_get_cable_type (struct max77843_muic_info*,int /*<<< orphan*/ ,int*) ; 
 int max77843_muic_set_path (struct max77843_muic_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int max77843_muic_chg_handler(struct max77843_muic_info *info)
{
	int ret, chg_type, gnd_type;
	bool attached;

	chg_type = max77843_muic_get_cable_type(info,
			MAX77843_CABLE_GROUP_CHG, &attached);

	dev_dbg(info->dev,
		"external connector is %s(chg_type:0x%x, prev_chg_type:0x%x)\n",
		attached ? "attached" : "detached",
		chg_type, info->prev_chg_type);

	switch (chg_type) {
	case MAX77843_MUIC_CHG_USB:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_USB,
					     attached, false);
		if (ret < 0)
			return ret;

		extcon_set_state_sync(info->edev, EXTCON_USB, attached);
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
					attached);
		break;
	case MAX77843_MUIC_CHG_DOWNSTREAM:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_OPEN,
					     attached, false);
		if (ret < 0)
			return ret;

		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_CDP,
					attached);
		break;
	case MAX77843_MUIC_CHG_DEDICATED:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_OPEN,
					     attached, false);
		if (ret < 0)
			return ret;

		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP,
					attached);
		break;
	case MAX77843_MUIC_CHG_SPECIAL_500MA:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_OPEN,
					     attached, false);
		if (ret < 0)
			return ret;

		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SLOW,
					attached);
		break;
	case MAX77843_MUIC_CHG_SPECIAL_1A:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_OPEN,
					     attached, false);
		if (ret < 0)
			return ret;

		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_FAST,
					attached);
		break;
	case MAX77843_MUIC_CHG_GND:
		gnd_type = max77843_muic_get_cable_type(info,
				MAX77843_CABLE_GROUP_ADC_GND, &attached);

		/* Charger cable on MHL accessory is attach or detach */
		if (gnd_type == MAX77843_MUIC_GND_MHL_VB)
			extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP,
						true);
		else if (gnd_type == MAX77843_MUIC_GND_MHL)
			extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP,
						false);
		break;
	case MAX77843_MUIC_CHG_DOCK:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP, attached);
		break;
	case MAX77843_MUIC_CHG_NONE:
		break;
	default:
		dev_err(info->dev,
			"failed to detect %s accessory (chg_type:0x%x)\n",
			attached ? "attached" : "detached", chg_type);

		max77843_muic_set_path(info, MAX77843_MUIC_CONTROL1_SW_OPEN,
				       attached, false);
		return -EINVAL;
	}

	return 0;
}