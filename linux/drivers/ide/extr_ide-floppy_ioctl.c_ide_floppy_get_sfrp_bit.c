#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ide_disk_obj {int /*<<< orphan*/  disk; } ;
struct ide_atapi_pc {int /*<<< orphan*/  req_xfer; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  atapi_flags; struct ide_disk_obj* driver_data; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDEFLOPPY_CAPABILITIES_PAGE ; 
 int /*<<< orphan*/  IDE_AFLAG_SRFP ; 
 int /*<<< orphan*/  PC_FLAG_SUPPRESS_ERROR ; 
 int /*<<< orphan*/  ide_floppy_create_mode_sense_cmd (struct ide_atapi_pc*,int /*<<< orphan*/ ) ; 
 scalar_t__ ide_queue_pc_tail (TYPE_1__*,int /*<<< orphan*/ ,struct ide_atapi_pc*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ide_floppy_get_sfrp_bit(ide_drive_t *drive, struct ide_atapi_pc *pc)
{
	struct ide_disk_obj *floppy = drive->driver_data;
	u8 buf[20];

	drive->atapi_flags &= ~IDE_AFLAG_SRFP;

	ide_floppy_create_mode_sense_cmd(pc, IDEFLOPPY_CAPABILITIES_PAGE);
	pc->flags |= PC_FLAG_SUPPRESS_ERROR;

	if (ide_queue_pc_tail(drive, floppy->disk, pc, buf, pc->req_xfer))
		return 1;

	if (buf[8 + 2] & 0x40)
		drive->atapi_flags |= IDE_AFLAG_SRFP;

	return 0;
}