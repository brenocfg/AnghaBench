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
struct pqi_ctrl_info {int /*<<< orphan*/  scan_mutex; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int ENXIO ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pqi_ctrl_offline (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_schedule_rescan_worker_delayed (struct pqi_ctrl_info*) ; 
 int pqi_update_scsi_devices (struct pqi_ctrl_info*) ; 

__attribute__((used)) static int pqi_scan_scsi_devices(struct pqi_ctrl_info *ctrl_info)
{
	int rc = 0;

	if (pqi_ctrl_offline(ctrl_info))
		return -ENXIO;

	if (!mutex_trylock(&ctrl_info->scan_mutex)) {
		pqi_schedule_rescan_worker_delayed(ctrl_info);
		rc = -EINPROGRESS;
	} else {
		rc = pqi_update_scsi_devices(ctrl_info);
		if (rc)
			pqi_schedule_rescan_worker_delayed(ctrl_info);
		mutex_unlock(&ctrl_info->scan_mutex);
	}

	return rc;
}