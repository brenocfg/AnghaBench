#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lba; } ;
struct cdrom_multisession {int /*<<< orphan*/  xa_flag; TYPE_1__ addr; } ;
struct cdrom_info {struct atapi_toc* toc; } ;
struct cdrom_device_info {TYPE_2__* handle; } ;
struct atapi_toc {int /*<<< orphan*/  xa_flag; int /*<<< orphan*/  last_session_lba; } ;
struct TYPE_5__ {int atapi_flags; struct cdrom_info* driver_data; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int IDE_AFLAG_TOC_VALID ; 
 int ide_cd_read_toc (TYPE_2__*) ; 

int ide_cdrom_get_last_session(struct cdrom_device_info *cdi,
			       struct cdrom_multisession *ms_info)
{
	struct atapi_toc *toc;
	ide_drive_t *drive = cdi->handle;
	struct cdrom_info *info = drive->driver_data;
	int ret;

	if ((drive->atapi_flags & IDE_AFLAG_TOC_VALID) == 0 || !info->toc) {
		ret = ide_cd_read_toc(drive);
		if (ret)
			return ret;
	}

	toc = info->toc;
	ms_info->addr.lba = toc->last_session_lba;
	ms_info->xa_flag = toc->xa_flag;

	return 0;
}