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
typedef  void* u16 ;
struct ec_params_external_power_limit_v1 {void* voltage_lim; void* current_lim; } ;
struct charger_data {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_EXTERNAL_POWER_LIMIT ; 
 int cros_usbpd_charger_ec_command (struct charger_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ec_params_external_power_limit_v1*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int cros_usbpd_charger_set_ext_power_limit(struct charger_data *charger,
						  u16 current_lim,
						  u16 voltage_lim)
{
	struct ec_params_external_power_limit_v1 req;
	int ret;

	req.current_lim = current_lim;
	req.voltage_lim = voltage_lim;

	ret = cros_usbpd_charger_ec_command(charger, 0,
					    EC_CMD_EXTERNAL_POWER_LIMIT,
					    &req, sizeof(req), NULL, 0);
	if (ret < 0)
		dev_err(charger->dev,
			"Unable to set the 'External Power Limit': %d\n", ret);

	return ret;
}