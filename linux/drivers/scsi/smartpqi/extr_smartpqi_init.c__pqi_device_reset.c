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
struct pqi_scsi_dev {int dummy; } ;
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int FAILED ; 
 unsigned long NO_TIMEOUT ; 
 unsigned long PQI_LUN_RESET_PENDING_IO_TIMEOUT_SECS ; 
 unsigned int PQI_LUN_RESET_RETRIES ; 
 int /*<<< orphan*/  PQI_LUN_RESET_RETRY_INTERVAL_MSECS ; 
 int SUCCESS ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int pqi_device_wait_for_pending_io (struct pqi_ctrl_info*,struct pqi_scsi_dev*,unsigned long) ; 
 int pqi_lun_reset (struct pqi_ctrl_info*,struct pqi_scsi_dev*) ; 

__attribute__((used)) static int _pqi_device_reset(struct pqi_ctrl_info *ctrl_info,
	struct pqi_scsi_dev *device)
{
	int rc;
	unsigned int retries;
	unsigned long timeout_secs;

	for (retries = 0;;) {
		rc = pqi_lun_reset(ctrl_info, device);
		if (rc != -EAGAIN || ++retries > PQI_LUN_RESET_RETRIES)
			break;
		msleep(PQI_LUN_RESET_RETRY_INTERVAL_MSECS);
	}

	timeout_secs = rc ? PQI_LUN_RESET_PENDING_IO_TIMEOUT_SECS : NO_TIMEOUT;

	rc |= pqi_device_wait_for_pending_io(ctrl_info, device, timeout_secs);

	return rc == 0 ? SUCCESS : FAILED;
}