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
struct unstripe_c {int chunk_shift; int unstripe_width; int unstripe_offset; int /*<<< orphan*/  chunk_size; } ;
struct dm_target {struct unstripe_c* private; } ;
struct TYPE_2__ {int bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  sector_div (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sector_t map_to_core(struct dm_target *ti, struct bio *bio)
{
	struct unstripe_c *uc = ti->private;
	sector_t sector = bio->bi_iter.bi_sector;
	sector_t tmp_sector = sector;

	/* Shift us up to the right "row" on the stripe */
	if (uc->chunk_shift)
		tmp_sector >>= uc->chunk_shift;
	else
		sector_div(tmp_sector, uc->chunk_size);

	sector += uc->unstripe_width * tmp_sector;

	/* Account for what stripe we're operating on */
	return sector + uc->unstripe_offset;
}