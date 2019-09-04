#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct linear_c {TYPE_1__* dev; } ;
struct dm_target {struct linear_c* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_2__ bi_iter; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 scalar_t__ REQ_OP_ZONE_RESET ; 
 scalar_t__ bio_op (struct bio*) ; 
 scalar_t__ bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linear_map_sector (struct dm_target*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void linear_map_bio(struct dm_target *ti, struct bio *bio)
{
	struct linear_c *lc = ti->private;

	bio_set_dev(bio, lc->dev->bdev);
	if (bio_sectors(bio) || bio_op(bio) == REQ_OP_ZONE_RESET)
		bio->bi_iter.bi_sector =
			linear_map_sector(ti, bio->bi_iter.bi_sector);
}