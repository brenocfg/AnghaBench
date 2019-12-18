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
struct scsi_device {int queue_depth; } ;

/* Variables and functions */
 int CXLFLASH_MAX_CMDS_PER_LUN ; 
 int /*<<< orphan*/  scsi_change_queue_depth (struct scsi_device*,int) ; 

__attribute__((used)) static int cxlflash_change_queue_depth(struct scsi_device *sdev, int qdepth)
{

	if (qdepth > CXLFLASH_MAX_CMDS_PER_LUN)
		qdepth = CXLFLASH_MAX_CMDS_PER_LUN;

	scsi_change_queue_depth(sdev, qdepth);
	return sdev->queue_depth;
}