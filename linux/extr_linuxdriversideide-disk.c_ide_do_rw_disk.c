#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  ide_startstop_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* rw_disk ) (TYPE_2__*,struct request*) ;} ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_7__ {int dev_flags; int /*<<< orphan*/  name; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IDE_DFLAG_BLOCKED ; 
 scalar_t__ READ ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  __ide_do_rw_disk (TYPE_2__*,struct request*,scalar_t__) ; 
 int blk_rq_is_passthrough (struct request*) ; 
 int /*<<< orphan*/  blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  ledtrig_disk_activity (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct request*) ; 

__attribute__((used)) static ide_startstop_t ide_do_rw_disk(ide_drive_t *drive, struct request *rq,
				      sector_t block)
{
	ide_hwif_t *hwif = drive->hwif;

	BUG_ON(drive->dev_flags & IDE_DFLAG_BLOCKED);
	BUG_ON(blk_rq_is_passthrough(rq));

	ledtrig_disk_activity(rq_data_dir(rq) == WRITE);

	pr_debug("%s: %sing: block=%llu, sectors=%u\n",
		 drive->name, rq_data_dir(rq) == READ ? "read" : "writ",
		 (unsigned long long)block, blk_rq_sectors(rq));

	if (hwif->rw_disk)
		hwif->rw_disk(drive, rq);

	return __ide_do_rw_disk(drive, rq, block);
}