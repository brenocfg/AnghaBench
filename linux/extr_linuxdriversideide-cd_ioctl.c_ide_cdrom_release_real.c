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
struct cdrom_device_info {int /*<<< orphan*/  use_count; TYPE_1__* handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  atapi_flags; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_AFLAG_TOC_VALID ; 

void ide_cdrom_release_real(struct cdrom_device_info *cdi)
{
	ide_drive_t *drive = cdi->handle;

	if (!cdi->use_count)
		drive->atapi_flags &= ~IDE_AFLAG_TOC_VALID;
}