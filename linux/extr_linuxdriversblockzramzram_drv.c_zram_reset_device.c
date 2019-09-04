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
typedef  scalar_t__ u64 ;
struct zram {int /*<<< orphan*/  stats; int /*<<< orphan*/  init_lock; TYPE_1__* disk; scalar_t__ disksize; struct zcomp* comp; scalar_t__ limit_pages; } ;
struct zcomp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_done (struct zram*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  part_stat_set_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_bdev (struct zram*) ; 
 int /*<<< orphan*/  set_capacity (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcomp_destroy (struct zcomp*) ; 
 int /*<<< orphan*/  zram_meta_free (struct zram*,scalar_t__) ; 

__attribute__((used)) static void zram_reset_device(struct zram *zram)
{
	struct zcomp *comp;
	u64 disksize;

	down_write(&zram->init_lock);

	zram->limit_pages = 0;

	if (!init_done(zram)) {
		up_write(&zram->init_lock);
		return;
	}

	comp = zram->comp;
	disksize = zram->disksize;
	zram->disksize = 0;

	set_capacity(zram->disk, 0);
	part_stat_set_all(&zram->disk->part0, 0);

	up_write(&zram->init_lock);
	/* I/O operation under all of CPU are done so let's free */
	zram_meta_free(zram, disksize);
	memset(&zram->stats, 0, sizeof(zram->stats));
	zcomp_destroy(comp);
	reset_bdev(zram);
}