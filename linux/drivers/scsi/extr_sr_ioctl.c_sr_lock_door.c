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
struct cdrom_device_info {TYPE_1__* handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
typedef  TYPE_1__ Scsi_CD ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_REMOVAL_ALLOW ; 
 int /*<<< orphan*/  SCSI_REMOVAL_PREVENT ; 
 int scsi_set_medium_removal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sr_lock_door(struct cdrom_device_info *cdi, int lock)
{
	Scsi_CD *cd = cdi->handle;

	return scsi_set_medium_removal(cd->device, lock ?
		       SCSI_REMOVAL_PREVENT : SCSI_REMOVAL_ALLOW);
}