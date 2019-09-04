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
struct cdrom_device_info {int options; } ;

/* Variables and functions */
 unsigned long CDC_LOCK ; 
#define  CDO_CHECK_TYPE 130 
#define  CDO_LOCK 129 
#define  CDO_USE_FFLAGS 128 
 int /*<<< orphan*/  CDROM_CAN (unsigned long) ; 
 int /*<<< orphan*/  CD_DO_IOCTL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  cd_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cdrom_ioctl_set_options(struct cdrom_device_info *cdi,
		unsigned long arg)
{
	cd_dbg(CD_DO_IOCTL, "entering CDROM_SET_OPTIONS\n");

	/*
	 * Options need to be in sync with capability.
	 * Too late for that, so we have to check each one separately.
	 */
	switch (arg) {
	case CDO_USE_FFLAGS:
	case CDO_CHECK_TYPE:
		break;
	case CDO_LOCK:
		if (!CDROM_CAN(CDC_LOCK))
			return -ENOSYS;
		break;
	case 0:
		return cdi->options;
	/* default is basically CDO_[AUTO_CLOSE|AUTO_EJECT] */
	default:
		if (!CDROM_CAN(arg))
			return -ENOSYS;
	}
	cdi->options |= (int) arg;
	return cdi->options;
}