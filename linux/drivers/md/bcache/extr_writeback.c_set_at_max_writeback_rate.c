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
struct TYPE_2__ {int /*<<< orphan*/  rate; } ;
struct cached_dev {scalar_t__ writeback_rate_change; scalar_t__ writeback_rate_integral_scaled; scalar_t__ writeback_rate_proportional; TYPE_1__ writeback_rate; } ;
struct cache_set {int /*<<< orphan*/  at_max_writeback_rate; int /*<<< orphan*/  attached_dev_nr; int /*<<< orphan*/  idle_counter; int /*<<< orphan*/  gc_mark_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool set_at_max_writeback_rate(struct cache_set *c,
				       struct cached_dev *dc)
{
	/* Don't set max writeback rate if gc is running */
	if (!c->gc_mark_valid)
		return false;
	/*
	 * Idle_counter is increased everytime when update_writeback_rate() is
	 * called. If all backing devices attached to the same cache set have
	 * identical dc->writeback_rate_update_seconds values, it is about 6
	 * rounds of update_writeback_rate() on each backing device before
	 * c->at_max_writeback_rate is set to 1, and then max wrteback rate set
	 * to each dc->writeback_rate.rate.
	 * In order to avoid extra locking cost for counting exact dirty cached
	 * devices number, c->attached_dev_nr is used to calculate the idle
	 * throushold. It might be bigger if not all cached device are in write-
	 * back mode, but it still works well with limited extra rounds of
	 * update_writeback_rate().
	 */
	if (atomic_inc_return(&c->idle_counter) <
	    atomic_read(&c->attached_dev_nr) * 6)
		return false;

	if (atomic_read(&c->at_max_writeback_rate) != 1)
		atomic_set(&c->at_max_writeback_rate, 1);

	atomic_long_set(&dc->writeback_rate.rate, INT_MAX);

	/* keep writeback_rate_target as existing value */
	dc->writeback_rate_proportional = 0;
	dc->writeback_rate_integral_scaled = 0;
	dc->writeback_rate_change = 0;

	/*
	 * Check c->idle_counter and c->at_max_writeback_rate agagain in case
	 * new I/O arrives during before set_at_max_writeback_rate() returns.
	 * Then the writeback rate is set to 1, and its new value should be
	 * decided via __update_writeback_rate().
	 */
	if ((atomic_read(&c->idle_counter) <
	     atomic_read(&c->attached_dev_nr) * 6) ||
	    !atomic_read(&c->at_max_writeback_rate))
		return false;

	return true;
}