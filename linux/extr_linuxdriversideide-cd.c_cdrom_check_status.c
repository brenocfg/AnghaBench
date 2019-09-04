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
struct scsi_sense_hdr {int dummy; } ;
struct cdrom_device_info {int sanyo_slot; } ;
struct cdrom_info {struct cdrom_device_info devinfo; } ;
struct TYPE_4__ {struct cdrom_info* driver_data; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int BLK_MAX_CDB ; 
 int EIO ; 
 unsigned char GPCMD_TEST_UNIT_READY ; 
 int /*<<< orphan*/  IDE_DBG_FUNC ; 
 int /*<<< orphan*/  RQF_QUIET ; 
 int ide_cd_queue_pc (TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct scsi_sense_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_debug_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

int cdrom_check_status(ide_drive_t *drive, struct scsi_sense_hdr *sshdr)
{
	struct cdrom_info *info = drive->driver_data;
	struct cdrom_device_info *cdi;
	unsigned char cmd[BLK_MAX_CDB];

	ide_debug_log(IDE_DBG_FUNC, "enter");

	if (!info)
		return -EIO;

	cdi = &info->devinfo;

	memset(cmd, 0, BLK_MAX_CDB);
	cmd[0] = GPCMD_TEST_UNIT_READY;

	/*
	 * Sanyo 3 CD changer uses byte 7 of TEST_UNIT_READY to switch CDs
	 * instead of supporting the LOAD_UNLOAD opcode.
	 */
	cmd[7] = cdi->sanyo_slot % 3;

	return ide_cd_queue_pc(drive, cmd, 0, NULL, NULL, sshdr, 0, RQF_QUIET);
}