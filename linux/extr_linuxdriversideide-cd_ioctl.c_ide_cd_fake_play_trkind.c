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
struct cdrom_ti {scalar_t__ cdti_trk0; scalar_t__ cdti_trk1; } ;
struct TYPE_2__ {unsigned long lba; } ;
struct atapi_toc_entry {TYPE_1__ addr; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int BLK_MAX_CDB ; 
 scalar_t__ CDROM_LEADOUT ; 
 int EINVAL ; 
 unsigned char GPCMD_PLAY_AUDIO_MSF ; 
 int ide_cd_get_toc_entry (int /*<<< orphan*/ *,scalar_t__,struct atapi_toc_entry**) ; 
 int ide_cd_queue_pc (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lba_to_msf (unsigned long,unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ide_cd_fake_play_trkind(ide_drive_t *drive, void *arg)
{
	struct cdrom_ti *ti = arg;
	struct atapi_toc_entry *first_toc, *last_toc;
	unsigned long lba_start, lba_end;
	int stat;
	unsigned char cmd[BLK_MAX_CDB];

	stat = ide_cd_get_toc_entry(drive, ti->cdti_trk0, &first_toc);
	if (stat)
		return stat;

	stat = ide_cd_get_toc_entry(drive, ti->cdti_trk1, &last_toc);
	if (stat)
		return stat;

	if (ti->cdti_trk1 != CDROM_LEADOUT)
		++last_toc;
	lba_start = first_toc->addr.lba;
	lba_end   = last_toc->addr.lba;

	if (lba_end <= lba_start)
		return -EINVAL;

	memset(cmd, 0, BLK_MAX_CDB);

	cmd[0] = GPCMD_PLAY_AUDIO_MSF;
	lba_to_msf(lba_start,   &cmd[3], &cmd[4], &cmd[5]);
	lba_to_msf(lba_end - 1, &cmd[6], &cmd[7], &cmd[8]);

	return ide_cd_queue_pc(drive, cmd, 0, NULL, NULL, NULL, 0, 0);
}