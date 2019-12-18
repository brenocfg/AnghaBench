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
struct request {int rq_flags; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int RQF_PREEMPT ; 
#define  SDEV_BLOCK 133 
#define  SDEV_CREATED_BLOCK 132 
#define  SDEV_DEL 131 
#define  SDEV_OFFLINE 130 
#define  SDEV_QUIESCE 129 
#define  SDEV_TRANSPORT_OFFLINE 128 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*) ; 

__attribute__((used)) static blk_status_t
scsi_prep_state_check(struct scsi_device *sdev, struct request *req)
{
	switch (sdev->sdev_state) {
	case SDEV_OFFLINE:
	case SDEV_TRANSPORT_OFFLINE:
		/*
		 * If the device is offline we refuse to process any
		 * commands.  The device must be brought online
		 * before trying any recovery commands.
		 */
		sdev_printk(KERN_ERR, sdev,
			    "rejecting I/O to offline device\n");
		return BLK_STS_IOERR;
	case SDEV_DEL:
		/*
		 * If the device is fully deleted, we refuse to
		 * process any commands as well.
		 */
		sdev_printk(KERN_ERR, sdev,
			    "rejecting I/O to dead device\n");
		return BLK_STS_IOERR;
	case SDEV_BLOCK:
	case SDEV_CREATED_BLOCK:
		return BLK_STS_RESOURCE;
	case SDEV_QUIESCE:
		/*
		 * If the devices is blocked we defer normal commands.
		 */
		if (req && !(req->rq_flags & RQF_PREEMPT))
			return BLK_STS_RESOURCE;
		return BLK_STS_OK;
	default:
		/*
		 * For any other not fully online state we only allow
		 * special commands.  In particular any user initiated
		 * command is not allowed.
		 */
		if (req && !(req->rq_flags & RQF_PREEMPT))
			return BLK_STS_IOERR;
		return BLK_STS_OK;
	}
}