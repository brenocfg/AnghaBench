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
struct cdrom_device_info {int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int ide_cd_lockdoor (int /*<<< orphan*/ *,int) ; 

int ide_cdrom_lock_door(struct cdrom_device_info *cdi, int lock)
{
	ide_drive_t *drive = cdi->handle;

	return ide_cd_lockdoor(drive, lock);
}