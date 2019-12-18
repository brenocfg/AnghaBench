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
struct scsi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ qedf_queue_depth ; 
 int /*<<< orphan*/  scsi_change_queue_depth (struct scsi_device*,scalar_t__) ; 

__attribute__((used)) static int qedf_slave_configure(struct scsi_device *sdev)
{
	if (qedf_queue_depth) {
		scsi_change_queue_depth(sdev, qedf_queue_depth);
	}

	return 0;
}