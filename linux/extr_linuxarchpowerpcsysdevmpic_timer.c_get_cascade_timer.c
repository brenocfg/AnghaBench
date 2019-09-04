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
typedef  scalar_t__ const u64 ;
struct timer_group_priv {int dummy; } ;
struct mpic_timer {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 scalar_t__ MAX_TICKS ; 
 scalar_t__ MAX_TICKS_CASCADE ; 
 struct mpic_timer* detect_idle_cascade_timer (struct timer_group_priv*) ; 
 int set_cascade_timer (struct timer_group_priv*,scalar_t__ const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mpic_timer *get_cascade_timer(struct timer_group_priv *priv,
					u64 ticks)
{
	struct mpic_timer *allocated_timer;

	/* Two cascade timers: Support the maximum time */
	const u64 max_ticks = (u64)MAX_TICKS * (u64)MAX_TICKS_CASCADE;
	int ret;

	if (ticks > max_ticks)
		return NULL;

	/* detect idle timer */
	allocated_timer = detect_idle_cascade_timer(priv);
	if (!allocated_timer)
		return NULL;

	/* set ticks to timer */
	ret = set_cascade_timer(priv, ticks, allocated_timer->num);
	if (ret < 0)
		return NULL;

	return allocated_timer;
}