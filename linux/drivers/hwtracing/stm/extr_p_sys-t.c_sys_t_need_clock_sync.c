#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ clocksync_interval; } ;
struct sys_t_output {scalar_t__ clocksync_jiffies; TYPE_1__ node; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool sys_t_need_clock_sync(struct sys_t_output *op)
{
	if (op->node.clocksync_interval &&
	    time_after(op->clocksync_jiffies + op->node.clocksync_interval,
		       jiffies)) {
		op->clocksync_jiffies = jiffies;

		return true;
	}

	return false;
}