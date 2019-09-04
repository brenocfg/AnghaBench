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
struct era {int /*<<< orphan*/  md; } ;
struct dm_target {struct era* private; } ;
struct bio {int bi_opf; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int DM_MAPIO_REMAPPED ; 
 int DM_MAPIO_SUBMITTED ; 
 int REQ_PREFLUSH ; 
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  defer_bio (struct era*,struct bio*) ; 
 int /*<<< orphan*/  get_block (struct era*,struct bio*) ; 
 int /*<<< orphan*/  metadata_current_marked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remap_to_origin (struct era*,struct bio*) ; 

__attribute__((used)) static int era_map(struct dm_target *ti, struct bio *bio)
{
	struct era *era = ti->private;
	dm_block_t block = get_block(era, bio);

	/*
	 * All bios get remapped to the origin device.  We do this now, but
	 * it may not get issued until later.  Depending on whether the
	 * block is marked in this era.
	 */
	remap_to_origin(era, bio);

	/*
	 * REQ_PREFLUSH bios carry no data, so we're not interested in them.
	 */
	if (!(bio->bi_opf & REQ_PREFLUSH) &&
	    (bio_data_dir(bio) == WRITE) &&
	    !metadata_current_marked(era->md, block)) {
		defer_bio(era, bio);
		return DM_MAPIO_SUBMITTED;
	}

	return DM_MAPIO_REMAPPED;
}