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
struct r5l_log {scalar_t__ r5c_journal_mode; int /*<<< orphan*/  io_mutex; TYPE_2__* current_io; } ;
struct TYPE_3__ {scalar_t__ bi_size; } ;
struct bio {TYPE_1__ bi_iter; int /*<<< orphan*/  bi_opf; } ;
struct TYPE_4__ {int has_flush; int has_null_flush; int /*<<< orphan*/  pending_stripe; int /*<<< orphan*/  flush_barriers; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ R5C_JOURNAL_MODE_WRITE_THROUGH ; 
 int /*<<< orphan*/  REQ_PREFLUSH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r5l_get_meta (struct r5l_log*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r5l_submit_current_io (struct r5l_log*) ; 

int r5l_handle_flush_request(struct r5l_log *log, struct bio *bio)
{
	if (log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_THROUGH) {
		/*
		 * in write through (journal only)
		 * we flush log disk cache first, then write stripe data to
		 * raid disks. So if bio is finished, the log disk cache is
		 * flushed already. The recovery guarantees we can recovery
		 * the bio from log disk, so we don't need to flush again
		 */
		if (bio->bi_iter.bi_size == 0) {
			bio_endio(bio);
			return 0;
		}
		bio->bi_opf &= ~REQ_PREFLUSH;
	} else {
		/* write back (with cache) */
		if (bio->bi_iter.bi_size == 0) {
			mutex_lock(&log->io_mutex);
			r5l_get_meta(log, 0);
			bio_list_add(&log->current_io->flush_barriers, bio);
			log->current_io->has_flush = 1;
			log->current_io->has_null_flush = 1;
			atomic_inc(&log->current_io->pending_stripe);
			r5l_submit_current_io(log);
			mutex_unlock(&log->io_mutex);
			return 0;
		}
	}
	return -EAGAIN;
}