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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct port_data {int port_number; int psy_status; int psy_usb_type; int psy_online; int /*<<< orphan*/  psy; TYPE_1__ psy_desc; int /*<<< orphan*/  psy_current_max; int /*<<< orphan*/  psy_voltage_max_design; int /*<<< orphan*/  psy_power_max; int /*<<< orphan*/  psy_voltage_now; struct charger_data* charger; } ;
struct TYPE_4__ {int /*<<< orphan*/  current_lim; int /*<<< orphan*/  current_max; int /*<<< orphan*/  voltage_now; int /*<<< orphan*/  voltage_max; } ;
struct ec_response_usb_pd_power_info {int role; int type; int /*<<< orphan*/  max_power; TYPE_2__ meas; int /*<<< orphan*/  dualrole; } ;
struct ec_params_usb_pd_power_info {int port; } ;
struct device {int dummy; } ;
struct charger_data {struct device* dev; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_USB_PD_POWER_INFO ; 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 void* POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_MAINS ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_USB ; 
 int POWER_SUPPLY_USB_TYPE_APPLE_BRICK_ID ; 
 int POWER_SUPPLY_USB_TYPE_C ; 
 int POWER_SUPPLY_USB_TYPE_CDP ; 
 int POWER_SUPPLY_USB_TYPE_DCP ; 
 int POWER_SUPPLY_USB_TYPE_PD ; 
 void* POWER_SUPPLY_USB_TYPE_PD_DRP ; 
 void* POWER_SUPPLY_USB_TYPE_SDP ; 
 int POWER_SUPPLY_USB_TYPE_UNKNOWN ; 
#define  USB_CHG_TYPE_BC12_CDP 141 
#define  USB_CHG_TYPE_BC12_DCP 140 
#define  USB_CHG_TYPE_BC12_SDP 139 
#define  USB_CHG_TYPE_C 138 
#define  USB_CHG_TYPE_NONE 137 
#define  USB_CHG_TYPE_OTHER 136 
#define  USB_CHG_TYPE_PD 135 
#define  USB_CHG_TYPE_PROPRIETARY 134 
#define  USB_CHG_TYPE_UNKNOWN 133 
#define  USB_CHG_TYPE_VBUS 132 
#define  USB_PD_PORT_POWER_DISCONNECTED 131 
#define  USB_PD_PORT_POWER_SINK 130 
#define  USB_PD_PORT_POWER_SINK_NOT_CHARGING 129 
#define  USB_PD_PORT_POWER_SOURCE 128 
 int cros_usbpd_charger_ec_command (struct charger_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ec_params_usb_pd_power_info*,int,struct ec_response_usb_pd_power_info*,int) ; 
 scalar_t__ cros_usbpd_charger_port_is_dedicated (struct port_data*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cros_usbpd_charger_get_power_info(struct port_data *port)
{
	struct charger_data *charger = port->charger;
	struct ec_response_usb_pd_power_info resp;
	struct ec_params_usb_pd_power_info req;
	int last_psy_status, last_psy_usb_type;
	struct device *dev = charger->dev;
	int ret;

	req.port = port->port_number;
	ret = cros_usbpd_charger_ec_command(charger, 0,
					    EC_CMD_USB_PD_POWER_INFO,
					    &req, sizeof(req),
					    &resp, sizeof(resp));
	if (ret < 0) {
		dev_err(dev, "Unable to query PD power info (err:0x%x)\n", ret);
		return ret;
	}

	last_psy_status = port->psy_status;
	last_psy_usb_type = port->psy_usb_type;

	switch (resp.role) {
	case USB_PD_PORT_POWER_DISCONNECTED:
		port->psy_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		port->psy_online = 0;
		break;
	case USB_PD_PORT_POWER_SOURCE:
		port->psy_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		port->psy_online = 0;
		break;
	case USB_PD_PORT_POWER_SINK:
		port->psy_status = POWER_SUPPLY_STATUS_CHARGING;
		port->psy_online = 1;
		break;
	case USB_PD_PORT_POWER_SINK_NOT_CHARGING:
		port->psy_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		port->psy_online = 1;
		break;
	default:
		dev_err(dev, "Unknown role %d\n", resp.role);
		break;
	}

	port->psy_voltage_max_design = resp.meas.voltage_max;
	port->psy_voltage_now = resp.meas.voltage_now;
	port->psy_current_max = resp.meas.current_max;
	port->psy_power_max = resp.max_power;

	switch (resp.type) {
	case USB_CHG_TYPE_BC12_SDP:
	case USB_CHG_TYPE_VBUS:
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_SDP;
		break;
	case USB_CHG_TYPE_NONE:
		/*
		 * For dual-role devices when we are a source, the firmware
		 * reports the type as NONE. Report such chargers as type
		 * USB_PD_DRP.
		 */
		if (resp.role == USB_PD_PORT_POWER_SOURCE && resp.dualrole)
			port->psy_usb_type = POWER_SUPPLY_USB_TYPE_PD_DRP;
		else
			port->psy_usb_type = POWER_SUPPLY_USB_TYPE_SDP;
		break;
	case USB_CHG_TYPE_OTHER:
	case USB_CHG_TYPE_PROPRIETARY:
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_APPLE_BRICK_ID;
		break;
	case USB_CHG_TYPE_C:
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_C;
		break;
	case USB_CHG_TYPE_BC12_DCP:
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_DCP;
		break;
	case USB_CHG_TYPE_BC12_CDP:
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_CDP;
		break;
	case USB_CHG_TYPE_PD:
		if (resp.dualrole)
			port->psy_usb_type = POWER_SUPPLY_USB_TYPE_PD_DRP;
		else
			port->psy_usb_type = POWER_SUPPLY_USB_TYPE_PD;
		break;
	case USB_CHG_TYPE_UNKNOWN:
		/*
		 * While the EC is trying to determine the type of charger that
		 * has been plugged in, it will report the charger type as
		 * unknown. Additionally since the power capabilities are
		 * unknown, report the max current and voltage as zero.
		 */
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_UNKNOWN;
		port->psy_voltage_max_design = 0;
		port->psy_current_max = 0;
		break;
	default:
		dev_err(dev, "Port %d: default case!\n", port->port_number);
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_SDP;
	}

	if (cros_usbpd_charger_port_is_dedicated(port))
		port->psy_desc.type = POWER_SUPPLY_TYPE_MAINS;
	else
		port->psy_desc.type = POWER_SUPPLY_TYPE_USB;

	dev_dbg(dev,
		"Port %d: type=%d vmax=%d vnow=%d cmax=%d clim=%d pmax=%d\n",
		port->port_number, resp.type, resp.meas.voltage_max,
		resp.meas.voltage_now, resp.meas.current_max,
		resp.meas.current_lim, resp.max_power);

	/*
	 * If power supply type or status changed, explicitly call
	 * power_supply_changed. This results in udev event getting generated
	 * and allows user mode apps to react quicker instead of waiting for
	 * their next poll of power supply status.
	 */
	if (last_psy_usb_type != port->psy_usb_type ||
	    last_psy_status != port->psy_status)
		power_supply_changed(port->psy);

	return 0;
}