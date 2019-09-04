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
struct global_pstate_info {scalar_t__ elapsed_time; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 unsigned int GPSTATE_TIMER_INTERVAL ; 
 scalar_t__ MAX_RAMP_DOWN_TIME ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (unsigned int) ; 

__attribute__((used)) static inline void  queue_gpstate_timer(struct global_pstate_info *gpstates)
{
	unsigned int timer_interval;

	/*
	 * Setting up timer to fire after GPSTATE_TIMER_INTERVAL ms, But
	 * if it exceeds MAX_RAMP_DOWN_TIME ms for ramp down time.
	 * Set timer such that it fires exactly at MAX_RAMP_DOWN_TIME
	 * seconds of ramp down time.
	 */
	if ((gpstates->elapsed_time + GPSTATE_TIMER_INTERVAL)
	     > MAX_RAMP_DOWN_TIME)
		timer_interval = MAX_RAMP_DOWN_TIME - gpstates->elapsed_time;
	else
		timer_interval = GPSTATE_TIMER_INTERVAL;

	mod_timer(&gpstates->timer, jiffies + msecs_to_jiffies(timer_interval));
}