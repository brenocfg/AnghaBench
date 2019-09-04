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
struct r5l_log {int /*<<< orphan*/  io_list_lock; } ;
struct r5l_io_unit {TYPE_1__* current_bio; scalar_t__ has_fua; scalar_t__ has_flush; TYPE_1__* split_bio; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_opf; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_UNIT_IO_START ; 
 int /*<<< orphan*/  REQ_FUA ; 
 int /*<<< orphan*/  REQ_PREFLUSH ; 
 int /*<<< orphan*/  __r5l_set_io_unit_state (struct r5l_io_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  submit_bio (TYPE_1__*) ; 

__attribute__((used)) static void r5l_do_submit_io(struct r5l_log *log, struct r5l_io_unit *io)
{
	unsigned long flags;

	spin_lock_irqsave(&log->io_list_lock, flags);
	__r5l_set_io_unit_state(io, IO_UNIT_IO_START);
	spin_unlock_irqrestore(&log->io_list_lock, flags);

	/*
	 * In case of journal device failures, submit_bio will get error
	 * and calls endio, then active stripes will continue write
	 * process. Therefore, it is not necessary to check Faulty bit
	 * of journal device here.
	 *
	 * We can't check split_bio after current_bio is submitted. If
	 * io->split_bio is null, after current_bio is submitted, current_bio
	 * might already be completed and the io_unit is freed. We submit
	 * split_bio first to avoid the issue.
	 */
	if (io->split_bio) {
		if (io->has_flush)
			io->split_bio->bi_opf |= REQ_PREFLUSH;
		if (io->has_fua)
			io->split_bio->bi_opf |= REQ_FUA;
		submit_bio(io->split_bio);
	}

	if (io->has_flush)
		io->current_bio->bi_opf |= REQ_PREFLUSH;
	if (io->has_fua)
		io->current_bio->bi_opf |= REQ_FUA;
	submit_bio(io->current_bio);
}