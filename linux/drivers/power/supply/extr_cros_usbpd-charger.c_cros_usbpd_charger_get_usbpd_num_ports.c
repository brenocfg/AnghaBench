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
struct ec_response_usb_pd_ports {int num_ports; } ;
struct charger_data {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  resp ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_USB_PD_PORTS ; 
 int cros_usbpd_charger_ec_command (struct charger_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ec_response_usb_pd_ports*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int cros_usbpd_charger_get_usbpd_num_ports(struct charger_data *charger)
{
	struct ec_response_usb_pd_ports resp;
	int ret;

	ret = cros_usbpd_charger_ec_command(charger, 0, EC_CMD_USB_PD_PORTS,
					    NULL, 0, &resp, sizeof(resp));
	if (ret < 0) {
		dev_err(charger->dev,
			"Unable to get the number or ports (err:0x%x)\n", ret);
		return ret;
	}

	return resp.num_ports;
}