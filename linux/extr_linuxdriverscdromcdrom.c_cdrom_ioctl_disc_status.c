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
struct TYPE_3__ {int error; scalar_t__ audio; scalar_t__ data; scalar_t__ cdi; scalar_t__ xa; } ;
typedef  TYPE_1__ tracktype ;
struct cdrom_device_info {int dummy; } ;

/* Variables and functions */
 int CDS_AUDIO ; 
 int CDS_DATA_1 ; 
 int CDS_MIXED ; 
 int CDS_NO_INFO ; 
 int CDS_XA_2_1 ; 
 int CDS_XA_2_2 ; 
 int /*<<< orphan*/  CD_DO_IOCTL ; 
 int /*<<< orphan*/  CD_WARNING ; 
 int /*<<< orphan*/  cd_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cdrom_count_tracks (struct cdrom_device_info*,TYPE_1__*) ; 

__attribute__((used)) static int cdrom_ioctl_disc_status(struct cdrom_device_info *cdi)
{
	tracktype tracks;

	cd_dbg(CD_DO_IOCTL, "entering CDROM_DISC_STATUS\n");

	cdrom_count_tracks(cdi, &tracks);
	if (tracks.error)
		return tracks.error;

	/* Policy mode on */
	if (tracks.audio > 0) {
		if (!tracks.data && !tracks.cdi && !tracks.xa)
			return CDS_AUDIO;
		else
			return CDS_MIXED;
	}

	if (tracks.cdi > 0)
		return CDS_XA_2_2;
	if (tracks.xa > 0)
		return CDS_XA_2_1;
	if (tracks.data > 0)
		return CDS_DATA_1;
	/* Policy mode off */

	cd_dbg(CD_WARNING, "This disc doesn't have any tracks I recognize!\n");
	return CDS_NO_INFO;
}