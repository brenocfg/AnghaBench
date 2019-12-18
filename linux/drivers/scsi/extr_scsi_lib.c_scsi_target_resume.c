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
struct scsi_target {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_resume_fn ; 
 int /*<<< orphan*/  starget_for_each_device (struct scsi_target*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
scsi_target_resume(struct scsi_target *starget)
{
	starget_for_each_device(starget, NULL, device_resume_fn);
}