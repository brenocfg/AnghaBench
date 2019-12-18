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
 scalar_t__ FW_FINAL ; 
 scalar_t__ FW_TRY ; 
 int /*<<< orphan*/  __obtain_firmware (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  fw_mutex ; 
 scalar_t__ fw_state ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int retry_firmware(struct hfi1_devdata *dd, int load_result)
{
	int retry;

	mutex_lock(&fw_mutex);

	if (load_result == 0) {
		/*
		 * The load succeeded, so expect all others to do the same.
		 * Do not retry again.
		 */
		if (fw_state == FW_TRY)
			fw_state = FW_FINAL;
		retry = 0;	/* do NOT retry */
	} else if (fw_state == FW_TRY) {
		/* load failed, obtain alternate firmware */
		__obtain_firmware(dd);
		retry = (fw_state == FW_FINAL);
	} else {
		/* else in FW_FINAL or FW_ERR, no retry in either case */
		retry = 0;
	}

	mutex_unlock(&fw_mutex);
	return retry;
}