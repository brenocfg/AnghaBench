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
struct scsi_device {int dummy; } ;
struct TYPE_2__ {int can_queue; } ;

/* Variables and functions */
 int scsi_change_queue_depth (struct scsi_device*,int) ; 
 TYPE_1__ scsi_driver ; 

__attribute__((used)) static int storvsc_change_queue_depth(struct scsi_device *sdev, int queue_depth)
{
	if (queue_depth > scsi_driver.can_queue)
		queue_depth = scsi_driver.can_queue;

	return scsi_change_queue_depth(sdev, queue_depth);
}