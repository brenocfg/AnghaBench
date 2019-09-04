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
struct unstripe_c {scalar_t__ physical_start; TYPE_1__* dev; } ;
struct dm_target {struct unstripe_c* private; } ;
struct TYPE_4__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_2__ bi_iter; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int DM_MAPIO_REMAPPED ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ map_to_core (struct dm_target*,struct bio*) ; 

__attribute__((used)) static int unstripe_map(struct dm_target *ti, struct bio *bio)
{
	struct unstripe_c *uc = ti->private;

	bio_set_dev(bio, uc->dev->bdev);
	bio->bi_iter.bi_sector = map_to_core(ti, bio) + uc->physical_start;

	return DM_MAPIO_REMAPPED;
}