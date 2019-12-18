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
struct ucsi_ccg {scalar_t__ fw_build; scalar_t__ fw_version; int /*<<< orphan*/  pm_work; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CCG_FW_BUILD_NVIDIA ; 
 scalar_t__ CCG_OLD_FW_VERSION ; 
 struct ucsi_ccg* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int ucsi_ccg_runtime_resume(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ucsi_ccg *uc = i2c_get_clientdata(client);

	/*
	 * Firmware version 3.1.10 or earlier, built for NVIDIA has known issue
	 * of missing interrupt when a device is connected for runtime resume.
	 * Schedule a work to call ISR as a workaround.
	 */
	if (uc->fw_build == CCG_FW_BUILD_NVIDIA &&
	    uc->fw_version <= CCG_OLD_FW_VERSION)
		schedule_work(&uc->pm_work);

	return 0;
}