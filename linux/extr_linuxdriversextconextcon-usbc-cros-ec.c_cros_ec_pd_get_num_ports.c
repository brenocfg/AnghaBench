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
struct cros_ec_extcon_info {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_USB_PD_PORTS ; 
 int cros_ec_pd_command (struct cros_ec_extcon_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ec_response_usb_pd_ports*,int) ; 

__attribute__((used)) static int cros_ec_pd_get_num_ports(struct cros_ec_extcon_info *info)
{
	struct ec_response_usb_pd_ports resp;
	int ret;

	ret = cros_ec_pd_command(info, EC_CMD_USB_PD_PORTS,
				 0, NULL, 0, &resp, sizeof(resp));
	if (ret < 0)
		return ret;

	return resp.num_ports;
}