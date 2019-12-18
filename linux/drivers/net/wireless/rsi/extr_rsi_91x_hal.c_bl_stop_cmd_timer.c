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
struct rsi_hw {int blcmd_timer_expired; int /*<<< orphan*/  bl_cmd_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bl_stop_cmd_timer(struct rsi_hw *adapter)
{
	adapter->blcmd_timer_expired = false;
	if (timer_pending(&adapter->bl_cmd_timer))
		del_timer(&adapter->bl_cmd_timer);

	return 0;
}