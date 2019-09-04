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
struct log_c {int flush_failed; int region_count; int log_dev_flush_failed; scalar_t__ touched_cleaned; scalar_t__ touched_dirtied; int /*<<< orphan*/  clean_bits; int /*<<< orphan*/  ti; } ;
struct dm_dirty_log {scalar_t__ (* flush_callback_fn ) (int /*<<< orphan*/ ) ;struct log_c* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  fail_log_device (struct log_c*) ; 
 int flush_header (struct log_c*) ; 
 int /*<<< orphan*/  log_clear_bit (struct log_c*,int /*<<< orphan*/ ,int) ; 
 int rw_header (struct log_c*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disk_flush(struct dm_dirty_log *log)
{
	int r, i;
	struct log_c *lc = log->context;

	/* only write if the log has changed */
	if (!lc->touched_cleaned && !lc->touched_dirtied)
		return 0;

	if (lc->touched_cleaned && log->flush_callback_fn &&
	    log->flush_callback_fn(lc->ti)) {
		/*
		 * At this point it is impossible to determine which
		 * regions are clean and which are dirty (without
		 * re-reading the log off disk). So mark all of them
		 * dirty.
		 */
		lc->flush_failed = 1;
		for (i = 0; i < lc->region_count; i++)
			log_clear_bit(lc, lc->clean_bits, i);
	}

	r = rw_header(lc, REQ_OP_WRITE);
	if (r)
		fail_log_device(lc);
	else {
		if (lc->touched_dirtied) {
			r = flush_header(lc);
			if (r) {
				lc->log_dev_flush_failed = 1;
				fail_log_device(lc);
			} else
				lc->touched_dirtied = 0;
		}
		lc->touched_cleaned = 0;
	}

	return r;
}