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
struct TYPE_4__ {void* set_max; void* usb_type_max; } ;
struct TYPE_3__ {int vbus_collapse; } ;
struct ab8500_charger {int usb_device_is_unrecognised; int is_aca_rid; TYPE_2__ max_usb_in_curr; int /*<<< orphan*/  dev; TYPE_1__ flags; int /*<<< orphan*/  parent; int /*<<< orphan*/  vbus_detected; } ;
typedef  enum ab8500_charger_link_status { ____Placeholder_ab8500_charger_link_status } ab8500_charger_link_status ;

/* Variables and functions */
 int ENXIO ; 
 void* USB_CH_IP_CUR_LVL_0P05 ; 
 void* USB_CH_IP_CUR_LVL_0P5 ; 
 void* USB_CH_IP_CUR_LVL_0P9 ; 
 void* USB_CH_IP_CUR_LVL_1P3 ; 
 void* USB_CH_IP_CUR_LVL_1P5 ; 
#define  USB_STAT_ACA_DOCK_CHARGER 147 
#define  USB_STAT_ACA_RID_A 146 
#define  USB_STAT_ACA_RID_B 145 
#define  USB_STAT_ACA_RID_C_HS 144 
#define  USB_STAT_ACA_RID_C_HS_CHIRP 143 
#define  USB_STAT_ACA_RID_C_NM 142 
#define  USB_STAT_CARKIT_1 141 
#define  USB_STAT_CARKIT_2 140 
#define  USB_STAT_CHARGER_LINE_1 139 
#define  USB_STAT_DEDICATED_CHG 138 
#define  USB_STAT_HM_IDGND 137 
#define  USB_STAT_HOST_CHG_HS 136 
#define  USB_STAT_HOST_CHG_HS_CHIRP 135 
#define  USB_STAT_HOST_CHG_NM 134 
#define  USB_STAT_NOT_CONFIGURED 133 
#define  USB_STAT_NOT_VALID_LINK 132 
#define  USB_STAT_RESERVED 131 
#define  USB_STAT_STD_HOST_C_NS 130 
#define  USB_STAT_STD_HOST_C_S 129 
#define  USB_STAT_STD_HOST_NC 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_ab8500 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab8500_charger_max_usb_curr(struct ab8500_charger *di,
		enum ab8500_charger_link_status link_status)
{
	int ret = 0;

	di->usb_device_is_unrecognised = false;

	/*
	 * Platform only supports USB 2.0.
	 * This means that charging current from USB source
	 * is maximum 500 mA. Every occurence of USB_STAT_*_HOST_*
	 * should set USB_CH_IP_CUR_LVL_0P5.
	 */

	switch (link_status) {
	case USB_STAT_STD_HOST_NC:
	case USB_STAT_STD_HOST_C_NS:
	case USB_STAT_STD_HOST_C_S:
		dev_dbg(di->dev, "USB Type - Standard host is "
			"detected through USB driver\n");
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		di->is_aca_rid = 0;
		break;
	case USB_STAT_HOST_CHG_HS_CHIRP:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		di->is_aca_rid = 0;
		break;
	case USB_STAT_HOST_CHG_HS:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		di->is_aca_rid = 0;
		break;
	case USB_STAT_ACA_RID_C_HS:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P9;
		di->is_aca_rid = 0;
		break;
	case USB_STAT_ACA_RID_A:
		/*
		 * Dedicated charger level minus maximum current accessory
		 * can consume (900mA). Closest level is 500mA
		 */
		dev_dbg(di->dev, "USB_STAT_ACA_RID_A detected\n");
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		di->is_aca_rid = 1;
		break;
	case USB_STAT_ACA_RID_B:
		/*
		 * Dedicated charger level minus 120mA (20mA for ACA and
		 * 100mA for potential accessory). Closest level is 1300mA
		 */
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_1P3;
		dev_dbg(di->dev, "USB Type - 0x%02x MaxCurr: %d", link_status,
				di->max_usb_in_curr.usb_type_max);
		di->is_aca_rid = 1;
		break;
	case USB_STAT_HOST_CHG_NM:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		di->is_aca_rid = 0;
		break;
	case USB_STAT_DEDICATED_CHG:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_1P5;
		di->is_aca_rid = 0;
		break;
	case USB_STAT_ACA_RID_C_HS_CHIRP:
	case USB_STAT_ACA_RID_C_NM:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_1P5;
		di->is_aca_rid = 1;
		break;
	case USB_STAT_NOT_CONFIGURED:
		if (di->vbus_detected) {
			di->usb_device_is_unrecognised = true;
			dev_dbg(di->dev, "USB Type - Legacy charger.\n");
			di->max_usb_in_curr.usb_type_max =
						USB_CH_IP_CUR_LVL_1P5;
			break;
		}
		/* else, fall through */
	case USB_STAT_HM_IDGND:
		dev_err(di->dev, "USB Type - Charging not allowed\n");
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P05;
		ret = -ENXIO;
		break;
	case USB_STAT_RESERVED:
		if (is_ab8500(di->parent)) {
			di->flags.vbus_collapse = true;
			dev_err(di->dev, "USB Type - USB_STAT_RESERVED "
						"VBUS has collapsed\n");
			ret = -ENXIO;
			break;
		} else {
			dev_dbg(di->dev, "USB Type - Charging not allowed\n");
			di->max_usb_in_curr.usb_type_max =
						USB_CH_IP_CUR_LVL_0P05;
			dev_dbg(di->dev, "USB Type - 0x%02x MaxCurr: %d",
				link_status,
				di->max_usb_in_curr.usb_type_max);
			ret = -ENXIO;
			break;
		}
	case USB_STAT_CARKIT_1:
	case USB_STAT_CARKIT_2:
	case USB_STAT_ACA_DOCK_CHARGER:
	case USB_STAT_CHARGER_LINE_1:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		dev_dbg(di->dev, "USB Type - 0x%02x MaxCurr: %d", link_status,
				di->max_usb_in_curr.usb_type_max);
		break;
	case USB_STAT_NOT_VALID_LINK:
		dev_err(di->dev, "USB Type invalid - try charging anyway\n");
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		break;

	default:
		dev_err(di->dev, "USB Type - Unknown\n");
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P05;
		ret = -ENXIO;
		break;
	};

	di->max_usb_in_curr.set_max = di->max_usb_in_curr.usb_type_max;
	dev_dbg(di->dev, "USB Type - 0x%02x MaxCurr: %d",
		link_status, di->max_usb_in_curr.set_max);

	return ret;
}