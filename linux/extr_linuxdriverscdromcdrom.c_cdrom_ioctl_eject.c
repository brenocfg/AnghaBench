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
struct cdrom_device_info {int use_count; TYPE_1__* ops; scalar_t__ keeplocked; } ;
struct TYPE_2__ {int (* lock_door ) (struct cdrom_device_info*,int /*<<< orphan*/ ) ;int (* tray_move ) (struct cdrom_device_info*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_LOCK ; 
 int /*<<< orphan*/  CDC_OPEN_TRAY ; 
 scalar_t__ CDROM_CAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CD_DO_IOCTL ; 
 int EBUSY ; 
 int ENOSYS ; 
 int /*<<< orphan*/  cd_dbg (int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct cdrom_device_info*,int /*<<< orphan*/ ) ; 
 int stub2 (struct cdrom_device_info*,int) ; 

__attribute__((used)) static int cdrom_ioctl_eject(struct cdrom_device_info *cdi)
{
	cd_dbg(CD_DO_IOCTL, "entering CDROMEJECT\n");

	if (!CDROM_CAN(CDC_OPEN_TRAY))
		return -ENOSYS;
	if (cdi->use_count != 1 || cdi->keeplocked)
		return -EBUSY;
	if (CDROM_CAN(CDC_LOCK)) {
		int ret = cdi->ops->lock_door(cdi, 0);
		if (ret)
			return ret;
	}

	return cdi->ops->tray_move(cdi, 1);
}