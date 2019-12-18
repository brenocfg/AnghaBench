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
struct at86rf230_local {int /*<<< orphan*/  state; int /*<<< orphan*/  state_complete; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  at86rf230_async_error (struct at86rf230_local*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  at86rf230_async_state_change (struct at86rf230_local*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at86rf230_sync_state_change_complete ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
at86rf230_sync_state_change(struct at86rf230_local *lp, unsigned int state)
{
	unsigned long rc;

	at86rf230_async_state_change(lp, &lp->state, state,
				     at86rf230_sync_state_change_complete);

	rc = wait_for_completion_timeout(&lp->state_complete,
					 msecs_to_jiffies(100));
	if (!rc) {
		at86rf230_async_error(lp, &lp->state, -ETIMEDOUT);
		return -ETIMEDOUT;
	}

	return 0;
}