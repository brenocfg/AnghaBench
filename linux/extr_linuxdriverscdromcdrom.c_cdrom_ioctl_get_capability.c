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
struct cdrom_device_info {int mask; TYPE_1__* ops; } ;
struct TYPE_2__ {int capability; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD_DO_IOCTL ; 
 int /*<<< orphan*/  cd_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cdrom_ioctl_get_capability(struct cdrom_device_info *cdi)
{
	cd_dbg(CD_DO_IOCTL, "entering CDROM_GET_CAPABILITY\n");
	return (cdi->ops->capability & ~cdi->mask);
}