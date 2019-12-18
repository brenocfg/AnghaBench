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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int aha152x_internal_queue (struct scsi_cmnd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (struct scsi_cmnd*)) ; 

__attribute__((used)) static int aha152x_queue_lck(struct scsi_cmnd *SCpnt,
			     void (*done)(struct scsi_cmnd *))
{
	return aha152x_internal_queue(SCpnt, NULL, 0, done);
}