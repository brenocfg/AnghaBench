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
struct st_data_s {scalar_t__ ll_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WAKE_UP_IND ; 
 scalar_t__ ST_LL_ASLEEP_TO_AWAKE ; 
 scalar_t__ ST_LL_AWAKE ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  send_ll_cmd (struct st_data_s*,int /*<<< orphan*/ ) ; 

void st_ll_wakeup(struct st_data_s *ll)
{
	if (likely(ll->ll_state != ST_LL_AWAKE)) {
		send_ll_cmd(ll, LL_WAKE_UP_IND);	/* WAKE_IND */
		ll->ll_state = ST_LL_ASLEEP_TO_AWAKE;
	} else {
		/* don't send the duplicate wake_indication */
		pr_err(" Chip already AWAKE ");
	}
}