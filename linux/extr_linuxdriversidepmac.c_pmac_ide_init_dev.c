#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* mdev; } ;
typedef  TYPE_3__ pmac_ide_hwif_t ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct TYPE_12__ {TYPE_1__ gendev; } ;
typedef  TYPE_4__ ide_hwif_t ;
struct TYPE_13__ {int /*<<< orphan*/  dev_flags; TYPE_4__* hwif; } ;
typedef  TYPE_5__ ide_drive_t ;
struct TYPE_10__ {int /*<<< orphan*/  media_bay; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_DFLAG_NOPROBE ; 
 scalar_t__ MB_CD ; 
 scalar_t__ check_media_bay (int /*<<< orphan*/ ) ; 
 TYPE_3__* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ on_media_bay (TYPE_3__*) ; 

__attribute__((used)) static void pmac_ide_init_dev(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	pmac_ide_hwif_t *pmif = dev_get_drvdata(hwif->gendev.parent);

	if (on_media_bay(pmif)) {
		if (check_media_bay(pmif->mdev->media_bay) == MB_CD) {
			drive->dev_flags &= ~IDE_DFLAG_NOPROBE;
			return;
		}
		drive->dev_flags |= IDE_DFLAG_NOPROBE;
	}
}