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
struct TYPE_5__ {int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  id; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_4__ {int host_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IDE_DFLAG_LBA48 ; 
 int IDE_HFLAG_NO_LBA48 ; 
 scalar_t__ ata_id_lba48_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_addressing(ide_drive_t *drive, int arg)
{
	if (arg < 0 || arg > 2)
		return -EINVAL;

	if (arg && ((drive->hwif->host_flags & IDE_HFLAG_NO_LBA48) ||
	    ata_id_lba48_enabled(drive->id) == 0))
		return -EIO;

	if (arg == 2)
		arg = 0;

	if (arg)
		drive->dev_flags |= IDE_DFLAG_LBA48;
	else
		drive->dev_flags &= ~IDE_DFLAG_LBA48;

	return 0;
}