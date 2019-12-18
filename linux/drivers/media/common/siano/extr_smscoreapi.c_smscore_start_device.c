#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smscore_device_t {int /*<<< orphan*/  device; int /*<<< orphan*/  devpath; } ;
struct TYPE_2__ {int default_mode; } ;

/* Variables and functions */
 int DEVICE_MODE_NONE ; 
 int SMS_BOARD_UNKNOWN ; 
 int /*<<< orphan*/  g_smscore_deviceslock ; 
 int /*<<< orphan*/  kmutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct smscore_device_t*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 TYPE_1__* sms_get_board (int) ; 
 int smscore_configure_board (struct smscore_device_t*) ; 
 int smscore_get_board_id (struct smscore_device_t*) ; 
 int /*<<< orphan*/  smscore_init_ir (struct smscore_device_t*) ; 
 int smscore_notify_callbacks (struct smscore_device_t*,int /*<<< orphan*/ ,int) ; 
 int smscore_registry_getmode (int /*<<< orphan*/ ) ; 
 int smscore_set_device_mode (struct smscore_device_t*,int) ; 

int smscore_start_device(struct smscore_device_t *coredev)
{
	int rc;
	int board_id = smscore_get_board_id(coredev);
	int mode = smscore_registry_getmode(coredev->devpath);

	/* Device is initialized as DEVICE_MODE_NONE */
	if (board_id != SMS_BOARD_UNKNOWN && mode == DEVICE_MODE_NONE)
		mode = sms_get_board(board_id)->default_mode;

	rc = smscore_set_device_mode(coredev, mode);
	if (rc < 0) {
		pr_info("set device mode failed , rc %d\n", rc);
		return rc;
	}
	rc = smscore_configure_board(coredev);
	if (rc < 0) {
		pr_info("configure board failed , rc %d\n", rc);
		return rc;
	}

	kmutex_lock(&g_smscore_deviceslock);

	rc = smscore_notify_callbacks(coredev, coredev->device, 1);
	smscore_init_ir(coredev);

	pr_debug("device %p started, rc %d\n", coredev, rc);

	kmutex_unlock(&g_smscore_deviceslock);

	return rc;
}