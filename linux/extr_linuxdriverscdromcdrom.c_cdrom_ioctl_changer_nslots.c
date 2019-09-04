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
struct cdrom_device_info {int capacity; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD_DO_IOCTL ; 
 int /*<<< orphan*/  cd_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cdrom_ioctl_changer_nslots(struct cdrom_device_info *cdi)
{
	cd_dbg(CD_DO_IOCTL, "entering CDROM_CHANGER_NSLOTS\n");
	return cdi->capacity;
}