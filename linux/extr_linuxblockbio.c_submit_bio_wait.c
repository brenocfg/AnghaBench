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
struct bio {int /*<<< orphan*/  bi_status; int /*<<< orphan*/  bi_opf; int /*<<< orphan*/  bi_end_io; int /*<<< orphan*/ * bi_private; TYPE_1__* bi_disk; } ;
struct TYPE_2__ {int /*<<< orphan*/  lockdep_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK_MAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQ_SYNC ; 
 int blk_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 int /*<<< orphan*/  submit_bio_wait_endio ; 
 int /*<<< orphan*/  wait_for_completion_io (int /*<<< orphan*/ *) ; 

int submit_bio_wait(struct bio *bio)
{
	DECLARE_COMPLETION_ONSTACK_MAP(done, bio->bi_disk->lockdep_map);

	bio->bi_private = &done;
	bio->bi_end_io = submit_bio_wait_endio;
	bio->bi_opf |= REQ_SYNC;
	submit_bio(bio);
	wait_for_completion_io(&done);

	return blk_status_to_errno(bio->bi_status);
}