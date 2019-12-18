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
struct uas_dev_info {int flags; } ;
struct scsi_device {int /*<<< orphan*/  request_queue; struct uas_dev_info* hostdata; TYPE_1__* host; } ;
struct TYPE_2__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int US_FL_MAX_SECTORS_240 ; 
 int US_FL_MAX_SECTORS_64 ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_queue_update_dma_alignment (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int uas_slave_alloc(struct scsi_device *sdev)
{
	struct uas_dev_info *devinfo =
		(struct uas_dev_info *)sdev->host->hostdata;

	sdev->hostdata = devinfo;

	/*
	 * The protocol has no requirements on alignment in the strict sense.
	 * Controllers may or may not have alignment restrictions.
	 * As this is not exported, we use an extremely conservative guess.
	 */
	blk_queue_update_dma_alignment(sdev->request_queue, (512 - 1));

	if (devinfo->flags & US_FL_MAX_SECTORS_64)
		blk_queue_max_hw_sectors(sdev->request_queue, 64);
	else if (devinfo->flags & US_FL_MAX_SECTORS_240)
		blk_queue_max_hw_sectors(sdev->request_queue, 240);

	return 0;
}