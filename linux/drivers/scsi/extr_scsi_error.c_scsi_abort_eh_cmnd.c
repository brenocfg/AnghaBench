#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  hostt; } ;

/* Variables and functions */
 scalar_t__ SUCCESS ; 
 scalar_t__ scsi_try_bus_device_reset (struct scsi_cmnd*) ; 
 scalar_t__ scsi_try_bus_reset (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_try_host_reset (struct scsi_cmnd*) ; 
 scalar_t__ scsi_try_target_reset (struct scsi_cmnd*) ; 
 scalar_t__ scsi_try_to_abort_cmd (int /*<<< orphan*/ ,struct scsi_cmnd*) ; 

__attribute__((used)) static void scsi_abort_eh_cmnd(struct scsi_cmnd *scmd)
{
	if (scsi_try_to_abort_cmd(scmd->device->host->hostt, scmd) != SUCCESS)
		if (scsi_try_bus_device_reset(scmd) != SUCCESS)
			if (scsi_try_target_reset(scmd) != SUCCESS)
				if (scsi_try_bus_reset(scmd) != SUCCESS)
					scsi_try_host_reset(scmd);
}