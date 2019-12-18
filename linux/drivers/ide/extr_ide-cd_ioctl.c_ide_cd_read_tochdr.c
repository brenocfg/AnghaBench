#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cdrom_tochdr {int /*<<< orphan*/  cdth_trk1; int /*<<< orphan*/  cdth_trk0; } ;
struct cdrom_info {struct atapi_toc* toc; } ;
struct TYPE_5__ {int /*<<< orphan*/  last_track; int /*<<< orphan*/  first_track; } ;
struct atapi_toc {TYPE_1__ hdr; } ;
struct TYPE_6__ {struct cdrom_info* driver_data; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int ide_cd_read_toc (TYPE_2__*) ; 

__attribute__((used)) static int ide_cd_read_tochdr(ide_drive_t *drive, void *arg)
{
	struct cdrom_info *cd = drive->driver_data;
	struct cdrom_tochdr *tochdr = arg;
	struct atapi_toc *toc;
	int stat;

	/* Make sure our saved TOC is valid. */
	stat = ide_cd_read_toc(drive);
	if (stat)
		return stat;

	toc = cd->toc;
	tochdr->cdth_trk0 = toc->hdr.first_track;
	tochdr->cdth_trk1 = toc->hdr.last_track;

	return 0;
}