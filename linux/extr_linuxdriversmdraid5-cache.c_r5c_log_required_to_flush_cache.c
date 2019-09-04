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
struct r5l_log {int /*<<< orphan*/  stripe_in_journal_count; } ;
struct r5conf {int max_degraded; int raid_disks; int group_cnt; struct r5l_log* log; } ;
typedef  int sector_t ;

/* Variables and functions */
 int BLOCK_SECTORS ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r5c_is_writeback (struct r5l_log*) ; 

__attribute__((used)) static sector_t r5c_log_required_to_flush_cache(struct r5conf *conf)
{
	struct r5l_log *log = conf->log;

	if (!r5c_is_writeback(log))
		return 0;

	return BLOCK_SECTORS *
		((conf->max_degraded + 1) * atomic_read(&log->stripe_in_journal_count) +
		 (conf->raid_disks - conf->max_degraded) * (conf->group_cnt + 1));
}