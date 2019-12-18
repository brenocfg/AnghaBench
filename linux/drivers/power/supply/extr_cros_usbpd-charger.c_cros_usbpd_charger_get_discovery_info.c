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
struct port_data {int /*<<< orphan*/  model_name; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  port_number; struct charger_data* charger; } ;
struct ec_params_usb_pd_info_request {int /*<<< orphan*/  port; } ;
struct ec_params_usb_pd_discovery_entry {int vid; int pid; int /*<<< orphan*/  ptype; } ;
struct charger_data {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_USB_PD_DISCOVERY ; 
 int cros_usbpd_charger_ec_command (struct charger_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ec_params_usb_pd_info_request*,int,struct ec_params_usb_pd_discovery_entry*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int cros_usbpd_charger_get_discovery_info(struct port_data *port)
{
	struct charger_data *charger = port->charger;
	struct ec_params_usb_pd_discovery_entry resp;
	struct ec_params_usb_pd_info_request req;
	int ret;

	req.port = port->port_number;

	ret = cros_usbpd_charger_ec_command(charger, 0,
					    EC_CMD_USB_PD_DISCOVERY,
					    &req, sizeof(req),
					    &resp, sizeof(resp));
	if (ret < 0) {
		dev_err(charger->dev,
			"Unable to query discovery info (err:0x%x)\n", ret);
		return ret;
	}

	dev_dbg(charger->dev, "Port %d: VID = 0x%x, PID=0x%x, PTYPE=0x%x\n",
		port->port_number, resp.vid, resp.pid, resp.ptype);

	snprintf(port->manufacturer, sizeof(port->manufacturer), "%x",
		 resp.vid);
	snprintf(port->model_name, sizeof(port->model_name), "%x", resp.pid);

	return 0;
}