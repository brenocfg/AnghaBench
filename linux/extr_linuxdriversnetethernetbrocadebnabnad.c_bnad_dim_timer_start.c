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
struct bnad {int cfg_flags; int /*<<< orphan*/  dim_timer; int /*<<< orphan*/  run_flags; } ;

/* Variables and functions */
 int BNAD_CF_DIM_ENABLED ; 
 int /*<<< orphan*/  BNAD_DIM_TIMER_FREQ ; 
 int /*<<< orphan*/  BNAD_RF_DIM_TIMER_RUNNING ; 
 int /*<<< orphan*/  bnad_dim_timeout ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bnad_dim_timer_start(struct bnad *bnad)
{
	if (bnad->cfg_flags & BNAD_CF_DIM_ENABLED &&
	    !test_bit(BNAD_RF_DIM_TIMER_RUNNING, &bnad->run_flags)) {
		timer_setup(&bnad->dim_timer, bnad_dim_timeout, 0);
		set_bit(BNAD_RF_DIM_TIMER_RUNNING, &bnad->run_flags);
		mod_timer(&bnad->dim_timer,
			  jiffies + msecs_to_jiffies(BNAD_DIM_TIMER_FREQ));
	}
}