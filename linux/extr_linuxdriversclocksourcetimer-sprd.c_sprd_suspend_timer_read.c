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
typedef  int u64 ;
struct clocksource {int mask; } ;

/* Variables and functions */
 scalar_t__ TIMER_VALUE_SHDW_LO ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  suspend_to ; 
 scalar_t__ timer_of_base (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 sprd_suspend_timer_read(struct clocksource *cs)
{
	return ~(u64)readl_relaxed(timer_of_base(&suspend_to) +
				   TIMER_VALUE_SHDW_LO) & cs->mask;
}