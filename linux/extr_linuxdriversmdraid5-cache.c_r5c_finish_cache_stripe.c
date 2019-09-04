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
struct stripe_head {size_t pd_idx; TYPE_1__* dev; int /*<<< orphan*/  state; TYPE_2__* raid_conf; } ;
struct r5l_log {scalar_t__ r5c_journal_mode; } ;
struct TYPE_4__ {struct r5l_log* log; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (scalar_t__) ; 
 scalar_t__ R5C_JOURNAL_MODE_WRITE_THROUGH ; 
 int /*<<< orphan*/  R5_InJournal ; 
 int /*<<< orphan*/  STRIPE_R5C_CACHING ; 
 int /*<<< orphan*/  r5c_handle_data_cached (struct stripe_head*) ; 
 int /*<<< orphan*/  r5c_handle_parity_cached (struct stripe_head*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r5c_finish_cache_stripe(struct stripe_head *sh)
{
	struct r5l_log *log = sh->raid_conf->log;

	if (log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_THROUGH) {
		BUG_ON(test_bit(STRIPE_R5C_CACHING, &sh->state));
		/*
		 * Set R5_InJournal for parity dev[pd_idx]. This means
		 * all data AND parity in the journal. For RAID 6, it is
		 * NOT necessary to set the flag for dev[qd_idx], as the
		 * two parities are written out together.
		 */
		set_bit(R5_InJournal, &sh->dev[sh->pd_idx].flags);
	} else if (test_bit(STRIPE_R5C_CACHING, &sh->state)) {
		r5c_handle_data_cached(sh);
	} else {
		r5c_handle_parity_cached(sh);
		set_bit(R5_InJournal, &sh->dev[sh->pd_idx].flags);
	}
}