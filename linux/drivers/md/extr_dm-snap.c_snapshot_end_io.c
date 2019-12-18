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
struct dm_target {struct dm_snapshot* private; } ;
struct dm_snapshot {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int DM_ENDIO_DONE ; 
 scalar_t__ is_bio_tracked (struct bio*) ; 
 int /*<<< orphan*/  stop_tracking_chunk (struct dm_snapshot*,struct bio*) ; 

__attribute__((used)) static int snapshot_end_io(struct dm_target *ti, struct bio *bio,
		blk_status_t *error)
{
	struct dm_snapshot *s = ti->private;

	if (is_bio_tracked(bio))
		stop_tracking_chunk(s, bio);

	return DM_ENDIO_DONE;
}