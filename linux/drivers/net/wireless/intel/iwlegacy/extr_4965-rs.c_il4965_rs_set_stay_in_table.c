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
typedef  scalar_t__ u8 ;
struct il_priv {int dummy; } ;
struct il_lq_sta {int stay_in_tbl; scalar_t__ action_counter; int /*<<< orphan*/  flush_timer; scalar_t__ total_success; scalar_t__ total_failed; scalar_t__ table_count; int /*<<< orphan*/  max_success_limit; int /*<<< orphan*/  max_failure_limit; int /*<<< orphan*/  table_count_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_RATE (char*) ; 
 int /*<<< orphan*/  IL_LEGACY_FAILURE_LIMIT ; 
 int /*<<< orphan*/  IL_LEGACY_SUCCESS_LIMIT ; 
 int /*<<< orphan*/  IL_LEGACY_TBL_COUNT ; 
 int /*<<< orphan*/  IL_NONE_LEGACY_FAILURE_LIMIT ; 
 int /*<<< orphan*/  IL_NONE_LEGACY_SUCCESS_LIMIT ; 
 int /*<<< orphan*/  IL_NONE_LEGACY_TBL_COUNT ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void
il4965_rs_set_stay_in_table(struct il_priv *il, u8 is_legacy,
			    struct il_lq_sta *lq_sta)
{
	D_RATE("we are staying in the same table\n");
	lq_sta->stay_in_tbl = 1;	/* only place this gets set */
	if (is_legacy) {
		lq_sta->table_count_limit = IL_LEGACY_TBL_COUNT;
		lq_sta->max_failure_limit = IL_LEGACY_FAILURE_LIMIT;
		lq_sta->max_success_limit = IL_LEGACY_SUCCESS_LIMIT;
	} else {
		lq_sta->table_count_limit = IL_NONE_LEGACY_TBL_COUNT;
		lq_sta->max_failure_limit = IL_NONE_LEGACY_FAILURE_LIMIT;
		lq_sta->max_success_limit = IL_NONE_LEGACY_SUCCESS_LIMIT;
	}
	lq_sta->table_count = 0;
	lq_sta->total_failed = 0;
	lq_sta->total_success = 0;
	lq_sta->flush_timer = jiffies;
	lq_sta->action_counter = 0;
}