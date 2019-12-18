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
struct per_bio_data {scalar_t__ bio_submitted; } ;
struct flakey_c {scalar_t__ corrupt_bio_rw; int /*<<< orphan*/  flags; scalar_t__ corrupt_bio_byte; } ;
struct dm_target {struct flakey_c* private; } ;
struct bio {int dummy; } ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 scalar_t__ BLK_STS_IOERR ; 
 int DM_ENDIO_DONE ; 
 int /*<<< orphan*/  DROP_WRITES ; 
 int /*<<< orphan*/  ERROR_WRITES ; 
 scalar_t__ READ ; 
 scalar_t__ REQ_OP_ZONE_RESET ; 
 scalar_t__ all_corrupt_bio_flags_match (struct bio*,struct flakey_c*) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  corrupt_bio_data (struct bio*,struct flakey_c*) ; 
 struct per_bio_data* dm_per_bio_data (struct bio*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flakey_end_io(struct dm_target *ti, struct bio *bio,
			 blk_status_t *error)
{
	struct flakey_c *fc = ti->private;
	struct per_bio_data *pb = dm_per_bio_data(bio, sizeof(struct per_bio_data));

	if (bio_op(bio) == REQ_OP_ZONE_RESET)
		return DM_ENDIO_DONE;

	if (!*error && pb->bio_submitted && (bio_data_dir(bio) == READ)) {
		if (fc->corrupt_bio_byte && (fc->corrupt_bio_rw == READ) &&
		    all_corrupt_bio_flags_match(bio, fc)) {
			/*
			 * Corrupt successful matching READs while in down state.
			 */
			corrupt_bio_data(bio, fc);

		} else if (!test_bit(DROP_WRITES, &fc->flags) &&
			   !test_bit(ERROR_WRITES, &fc->flags)) {
			/*
			 * Error read during the down_interval if drop_writes
			 * and error_writes were not configured.
			 */
			*error = BLK_STS_IOERR;
		}
	}

	return DM_ENDIO_DONE;
}