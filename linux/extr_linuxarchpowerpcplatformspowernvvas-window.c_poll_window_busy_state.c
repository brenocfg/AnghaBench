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
typedef  scalar_t__ u64 ;
struct vas_window {int dummy; } ;

/* Variables and functions */
 int GET_FIELD (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  VAS_WIN_BUSY ; 
 int /*<<< orphan*/  VREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIN_STATUS ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ read_hvwc_reg (struct vas_window*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poll_window_busy_state(struct vas_window *window)
{
	int busy;
	u64 val;

retry:
	val = read_hvwc_reg(window, VREG(WIN_STATUS));
	busy = GET_FIELD(VAS_WIN_BUSY, val);
	if (busy) {
		val = 0;
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout(msecs_to_jiffies(5));
		goto retry;
	}
}