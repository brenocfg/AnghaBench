#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct vchiq_arm_state {int suspend_timer_running; TYPE_1__ suspend_timer; int /*<<< orphan*/  suspend_timer_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

inline void
start_suspend_timer(struct vchiq_arm_state *arm_state)
{
	del_timer(&arm_state->suspend_timer);
	arm_state->suspend_timer.expires = jiffies +
		msecs_to_jiffies(arm_state->suspend_timer_timeout);
	add_timer(&arm_state->suspend_timer);
	arm_state->suspend_timer_running = 1;
}