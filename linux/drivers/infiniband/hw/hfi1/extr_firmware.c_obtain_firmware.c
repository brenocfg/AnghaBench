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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ FW_EMPTY ; 
 scalar_t__ FW_ERR ; 
 scalar_t__ FW_TRY ; 
 int /*<<< orphan*/  __obtain_firmware (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int fw_err ; 
 int /*<<< orphan*/  fw_mutex ; 
 scalar_t__ fw_state ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int obtain_firmware(struct hfi1_devdata *dd)
{
	unsigned long timeout;

	mutex_lock(&fw_mutex);

	/* 40s delay due to long delay on missing firmware on some systems */
	timeout = jiffies + msecs_to_jiffies(40000);
	while (fw_state == FW_TRY) {
		/*
		 * Another device is trying the firmware.  Wait until it
		 * decides what works (or not).
		 */
		if (time_after(jiffies, timeout)) {
			/* waited too long */
			dd_dev_err(dd, "Timeout waiting for firmware try");
			fw_state = FW_ERR;
			fw_err = -ETIMEDOUT;
			break;
		}
		mutex_unlock(&fw_mutex);
		msleep(20);	/* arbitrary delay */
		mutex_lock(&fw_mutex);
	}
	/* not in FW_TRY state */

	/* set fw_state to FW_TRY, FW_FINAL, or FW_ERR, and fw_err */
	if (fw_state == FW_EMPTY)
		__obtain_firmware(dd);

	mutex_unlock(&fw_mutex);
	return fw_err;
}