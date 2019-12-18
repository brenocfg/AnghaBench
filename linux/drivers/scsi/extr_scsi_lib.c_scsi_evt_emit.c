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
struct scsi_event {int evt_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct scsi_device {TYPE_1__ sdev_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
#define  SDEV_EVT_ALUA_STATE_CHANGE_REPORTED 135 
#define  SDEV_EVT_CAPACITY_CHANGE_REPORTED 134 
#define  SDEV_EVT_INQUIRY_CHANGE_REPORTED 133 
#define  SDEV_EVT_LUN_CHANGE_REPORTED 132 
#define  SDEV_EVT_MEDIA_CHANGE 131 
#define  SDEV_EVT_MODE_PARAMETER_CHANGE_REPORTED 130 
#define  SDEV_EVT_POWER_ON_RESET_OCCURRED 129 
#define  SDEV_EVT_SOFT_THRESHOLD_REACHED_REPORTED 128 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  scsi_rescan_device (TYPE_1__*) ; 

__attribute__((used)) static void scsi_evt_emit(struct scsi_device *sdev, struct scsi_event *evt)
{
	int idx = 0;
	char *envp[3];

	switch (evt->evt_type) {
	case SDEV_EVT_MEDIA_CHANGE:
		envp[idx++] = "SDEV_MEDIA_CHANGE=1";
		break;
	case SDEV_EVT_INQUIRY_CHANGE_REPORTED:
		scsi_rescan_device(&sdev->sdev_gendev);
		envp[idx++] = "SDEV_UA=INQUIRY_DATA_HAS_CHANGED";
		break;
	case SDEV_EVT_CAPACITY_CHANGE_REPORTED:
		envp[idx++] = "SDEV_UA=CAPACITY_DATA_HAS_CHANGED";
		break;
	case SDEV_EVT_SOFT_THRESHOLD_REACHED_REPORTED:
	       envp[idx++] = "SDEV_UA=THIN_PROVISIONING_SOFT_THRESHOLD_REACHED";
		break;
	case SDEV_EVT_MODE_PARAMETER_CHANGE_REPORTED:
		envp[idx++] = "SDEV_UA=MODE_PARAMETERS_CHANGED";
		break;
	case SDEV_EVT_LUN_CHANGE_REPORTED:
		envp[idx++] = "SDEV_UA=REPORTED_LUNS_DATA_HAS_CHANGED";
		break;
	case SDEV_EVT_ALUA_STATE_CHANGE_REPORTED:
		envp[idx++] = "SDEV_UA=ASYMMETRIC_ACCESS_STATE_CHANGED";
		break;
	case SDEV_EVT_POWER_ON_RESET_OCCURRED:
		envp[idx++] = "SDEV_UA=POWER_ON_RESET_OCCURRED";
		break;
	default:
		/* do nothing */
		break;
	}

	envp[idx++] = NULL;

	kobject_uevent_env(&sdev->sdev_gendev.kobj, KOBJ_CHANGE, envp);
}