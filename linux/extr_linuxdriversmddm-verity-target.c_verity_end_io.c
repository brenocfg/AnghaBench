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
struct dm_verity_io {int /*<<< orphan*/  work; TYPE_1__* v; } ;
struct bio {int /*<<< orphan*/  bi_status; struct dm_verity_io* bi_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  verify_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verity_fec_is_enabled (TYPE_1__*) ; 
 int /*<<< orphan*/  verity_finish_io (struct dm_verity_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verity_work ; 

__attribute__((used)) static void verity_end_io(struct bio *bio)
{
	struct dm_verity_io *io = bio->bi_private;

	if (bio->bi_status && !verity_fec_is_enabled(io->v)) {
		verity_finish_io(io, bio->bi_status);
		return;
	}

	INIT_WORK(&io->work, verity_work);
	queue_work(io->v->verify_wq, &io->work);
}