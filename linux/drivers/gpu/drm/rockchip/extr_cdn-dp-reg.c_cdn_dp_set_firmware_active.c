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
typedef  int u8 ;
struct cdn_dp_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int FW_ACTIVE ; 
 int FW_STANDBY ; 
 int GENERAL_MAIN_CONTROL ; 
 int MB_MODULE_ID_GENERAL ; 
 int cdn_dp_mailbox_read (struct cdn_dp_device*) ; 
 int cdp_dp_mailbox_write (struct cdn_dp_device*,int) ; 

int cdn_dp_set_firmware_active(struct cdn_dp_device *dp, bool enable)
{
	u8 msg[5];
	int ret, i;

	msg[0] = GENERAL_MAIN_CONTROL;
	msg[1] = MB_MODULE_ID_GENERAL;
	msg[2] = 0;
	msg[3] = 1;
	msg[4] = enable ? FW_ACTIVE : FW_STANDBY;

	for (i = 0; i < sizeof(msg); i++) {
		ret = cdp_dp_mailbox_write(dp, msg[i]);
		if (ret)
			goto err_set_firmware_active;
	}

	/* read the firmware state */
	for (i = 0; i < sizeof(msg); i++)  {
		ret = cdn_dp_mailbox_read(dp);
		if (ret < 0)
			goto err_set_firmware_active;

		msg[i] = ret;
	}

	ret = 0;

err_set_firmware_active:
	if (ret < 0)
		DRM_DEV_ERROR(dp->dev, "set firmware active failed\n");
	return ret;
}