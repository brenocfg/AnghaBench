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
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  SCSI_LOG_ERROR_RECOVERY (int,int /*<<< orphan*/ ) ; 
#define  SDEV_BLOCK 136 
#define  SDEV_CANCEL 135 
#define  SDEV_CREATED 134 
#define  SDEV_CREATED_BLOCK 133 
#define  SDEV_DEL 132 
#define  SDEV_OFFLINE 131 
#define  SDEV_QUIESCE 130 
#define  SDEV_RUNNING 129 
#define  SDEV_TRANSPORT_OFFLINE 128 
 int /*<<< orphan*/  scsi_device_state_name (int) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
scsi_device_set_state(struct scsi_device *sdev, enum scsi_device_state state)
{
	enum scsi_device_state oldstate = sdev->sdev_state;

	if (state == oldstate)
		return 0;

	switch (state) {
	case SDEV_CREATED:
		switch (oldstate) {
		case SDEV_CREATED_BLOCK:
			break;
		default:
			goto illegal;
		}
		break;
			
	case SDEV_RUNNING:
		switch (oldstate) {
		case SDEV_CREATED:
		case SDEV_OFFLINE:
		case SDEV_TRANSPORT_OFFLINE:
		case SDEV_QUIESCE:
		case SDEV_BLOCK:
			break;
		default:
			goto illegal;
		}
		break;

	case SDEV_QUIESCE:
		switch (oldstate) {
		case SDEV_RUNNING:
		case SDEV_OFFLINE:
		case SDEV_TRANSPORT_OFFLINE:
			break;
		default:
			goto illegal;
		}
		break;

	case SDEV_OFFLINE:
	case SDEV_TRANSPORT_OFFLINE:
		switch (oldstate) {
		case SDEV_CREATED:
		case SDEV_RUNNING:
		case SDEV_QUIESCE:
		case SDEV_BLOCK:
			break;
		default:
			goto illegal;
		}
		break;

	case SDEV_BLOCK:
		switch (oldstate) {
		case SDEV_RUNNING:
		case SDEV_CREATED_BLOCK:
		case SDEV_OFFLINE:
			break;
		default:
			goto illegal;
		}
		break;

	case SDEV_CREATED_BLOCK:
		switch (oldstate) {
		case SDEV_CREATED:
			break;
		default:
			goto illegal;
		}
		break;

	case SDEV_CANCEL:
		switch (oldstate) {
		case SDEV_CREATED:
		case SDEV_RUNNING:
		case SDEV_QUIESCE:
		case SDEV_OFFLINE:
		case SDEV_TRANSPORT_OFFLINE:
			break;
		default:
			goto illegal;
		}
		break;

	case SDEV_DEL:
		switch (oldstate) {
		case SDEV_CREATED:
		case SDEV_RUNNING:
		case SDEV_OFFLINE:
		case SDEV_TRANSPORT_OFFLINE:
		case SDEV_CANCEL:
		case SDEV_BLOCK:
		case SDEV_CREATED_BLOCK:
			break;
		default:
			goto illegal;
		}
		break;

	}
	sdev->sdev_state = state;
	return 0;

 illegal:
	SCSI_LOG_ERROR_RECOVERY(1,
				sdev_printk(KERN_ERR, sdev,
					    "Illegal state transition %s->%s",
					    scsi_device_state_name(oldstate),
					    scsi_device_state_name(state))
				);
	return -EINVAL;
}