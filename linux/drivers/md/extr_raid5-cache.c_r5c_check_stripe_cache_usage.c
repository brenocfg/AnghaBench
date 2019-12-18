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
struct r5conf {int min_nr_stripes; int /*<<< orphan*/  log; int /*<<< orphan*/  empty_inactive_list_nr; int /*<<< orphan*/  r5c_cached_full_stripes; int /*<<< orphan*/  r5c_cached_partial_stripes; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r5c_is_writeback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r5l_wake_reclaim (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void r5c_check_stripe_cache_usage(struct r5conf *conf)
{
	int total_cached;

	if (!r5c_is_writeback(conf->log))
		return;

	total_cached = atomic_read(&conf->r5c_cached_partial_stripes) +
		atomic_read(&conf->r5c_cached_full_stripes);

	/*
	 * The following condition is true for either of the following:
	 *   - stripe cache pressure high:
	 *          total_cached > 3/4 min_nr_stripes ||
	 *          empty_inactive_list_nr > 0
	 *   - stripe cache pressure moderate:
	 *          total_cached > 1/2 min_nr_stripes
	 */
	if (total_cached > conf->min_nr_stripes * 1 / 2 ||
	    atomic_read(&conf->empty_inactive_list_nr) > 0)
		r5l_wake_reclaim(conf->log, 0);
}