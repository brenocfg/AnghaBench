#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct switch_ctx {TYPE_3__* path_list; } ;
struct dm_target {struct switch_ctx* private; } ;
struct TYPE_4__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_6__ {scalar_t__ start; TYPE_2__* dmdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int DM_MAPIO_REMAPPED ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ dm_target_offset (struct dm_target*,scalar_t__) ; 
 unsigned int switch_get_path_nr (struct switch_ctx*,scalar_t__) ; 

__attribute__((used)) static int switch_map(struct dm_target *ti, struct bio *bio)
{
	struct switch_ctx *sctx = ti->private;
	sector_t offset = dm_target_offset(ti, bio->bi_iter.bi_sector);
	unsigned path_nr = switch_get_path_nr(sctx, offset);

	bio_set_dev(bio, sctx->path_list[path_nr].dmdev->bdev);
	bio->bi_iter.bi_sector = sctx->path_list[path_nr].start + offset;

	return DM_MAPIO_REMAPPED;
}