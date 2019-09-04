#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct packet_command {int dummy; } ;
struct cdrom_device_info {int dummy; } ;
struct cdrom_info {struct cdrom_device_info devinfo; } ;
struct TYPE_3__ {int atapi_flags; struct cdrom_info* driver_data; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ ATAPI_CAPABILITIES_PAGE_PAD_SIZE ; 
 int ATAPI_CAPABILITIES_PAGE_SIZE ; 
 int /*<<< orphan*/  CGC_DATA_UNKNOWN ; 
 int /*<<< orphan*/  GPMODE_CAPABILITIES_PAGE ; 
 int IDE_AFLAG_FULL_CAPS_PAGE ; 
 int /*<<< orphan*/  IDE_DBG_FUNC ; 
 int cdrom_mode_sense (struct cdrom_device_info*,struct packet_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_debug_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int ide_cdrom_get_capabilities(ide_drive_t *drive, u8 *buf)
{
	struct cdrom_info *info = drive->driver_data;
	struct cdrom_device_info *cdi = &info->devinfo;
	struct packet_command cgc;
	int stat, attempts = 3, size = ATAPI_CAPABILITIES_PAGE_SIZE;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	if ((drive->atapi_flags & IDE_AFLAG_FULL_CAPS_PAGE) == 0)
		size -= ATAPI_CAPABILITIES_PAGE_PAD_SIZE;

	init_cdrom_command(&cgc, buf, size, CGC_DATA_UNKNOWN);
	do {
		/* we seem to get stat=0x01,err=0x00 the first time (??) */
		stat = cdrom_mode_sense(cdi, &cgc, GPMODE_CAPABILITIES_PAGE, 0);
		if (!stat)
			break;
	} while (--attempts);
	return stat;
}