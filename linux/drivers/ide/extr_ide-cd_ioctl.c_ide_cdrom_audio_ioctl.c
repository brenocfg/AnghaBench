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
struct cdrom_device_info {int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
#define  CDROMPLAYTRKIND 130 
#define  CDROMREADTOCENTRY 129 
#define  CDROMREADTOCHDR 128 
 int EINVAL ; 
 int ide_cd_fake_play_trkind (int /*<<< orphan*/ *,void*) ; 
 int ide_cd_read_tocentry (int /*<<< orphan*/ *,void*) ; 
 int ide_cd_read_tochdr (int /*<<< orphan*/ *,void*) ; 

int ide_cdrom_audio_ioctl(struct cdrom_device_info *cdi,
			  unsigned int cmd, void *arg)
{
	ide_drive_t *drive = cdi->handle;

	switch (cmd) {
	/*
	 * emulate PLAY_AUDIO_TI command with PLAY_AUDIO_10, since
	 * atapi doesn't support it
	 */
	case CDROMPLAYTRKIND:
		return ide_cd_fake_play_trkind(drive, arg);
	case CDROMREADTOCHDR:
		return ide_cd_read_tochdr(drive, arg);
	case CDROMREADTOCENTRY:
		return ide_cd_read_tocentry(drive, arg);
	default:
		return -EINVAL;
	}
}