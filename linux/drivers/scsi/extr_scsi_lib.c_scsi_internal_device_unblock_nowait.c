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
struct scsi_device {int sdev_state; } ;
typedef  enum scsi_device_state { ____Placeholder_scsi_device_state } scsi_device_state ;

/* Variables and functions */
 int EINVAL ; 
#define  SDEV_BLOCK 133 
#define  SDEV_CANCEL 132 
 int SDEV_CREATED ; 
#define  SDEV_CREATED_BLOCK 131 
#define  SDEV_OFFLINE 130 
#define  SDEV_RUNNING 129 
#define  SDEV_TRANSPORT_OFFLINE 128 
 int /*<<< orphan*/  scsi_start_queue (struct scsi_device*) ; 

int scsi_internal_device_unblock_nowait(struct scsi_device *sdev,
					enum scsi_device_state new_state)
{
	switch (new_state) {
	case SDEV_RUNNING:
	case SDEV_TRANSPORT_OFFLINE:
		break;
	default:
		return -EINVAL;
	}

	/*
	 * Try to transition the scsi device to SDEV_RUNNING or one of the
	 * offlined states and goose the device queue if successful.
	 */
	switch (sdev->sdev_state) {
	case SDEV_BLOCK:
	case SDEV_TRANSPORT_OFFLINE:
		sdev->sdev_state = new_state;
		break;
	case SDEV_CREATED_BLOCK:
		if (new_state == SDEV_TRANSPORT_OFFLINE ||
		    new_state == SDEV_OFFLINE)
			sdev->sdev_state = new_state;
		else
			sdev->sdev_state = SDEV_CREATED;
		break;
	case SDEV_CANCEL:
	case SDEV_OFFLINE:
		break;
	default:
		return -EINVAL;
	}
	scsi_start_queue(sdev);

	return 0;
}