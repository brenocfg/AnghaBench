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
struct goodix_ts_data {int /*<<< orphan*/  firmware_loading_complete; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  goodix_configure_dev (struct goodix_ts_data*) ; 
 int goodix_send_cfg (struct goodix_ts_data*,struct firmware const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 

__attribute__((used)) static void goodix_config_cb(const struct firmware *cfg, void *ctx)
{
	struct goodix_ts_data *ts = ctx;
	int error;

	if (cfg) {
		/* send device configuration to the firmware */
		error = goodix_send_cfg(ts, cfg);
		if (error)
			goto err_release_cfg;
	}

	goodix_configure_dev(ts);

err_release_cfg:
	release_firmware(cfg);
	complete_all(&ts->firmware_loading_complete);
}