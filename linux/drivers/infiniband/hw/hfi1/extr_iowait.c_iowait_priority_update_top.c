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
typedef  int /*<<< orphan*/  uint ;
typedef  scalar_t__ u8 ;
struct iowait {int priority; scalar_t__ starved_cnt; } ;

/* Variables and functions */
 int IOWAIT_PRIORITY_STARVE_SHIFT ; 

uint iowait_priority_update_top(struct iowait *w,
				struct iowait *top,
				uint idx, uint top_idx)
{
	u8 cnt, tcnt;

	/* Convert priority into starve_cnt and compare the total.*/
	cnt = (w->priority << IOWAIT_PRIORITY_STARVE_SHIFT) + w->starved_cnt;
	tcnt = (top->priority << IOWAIT_PRIORITY_STARVE_SHIFT) +
		top->starved_cnt;
	if (cnt > tcnt)
		return idx;
	else
		return top_idx;
}