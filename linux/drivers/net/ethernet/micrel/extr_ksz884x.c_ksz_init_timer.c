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
struct ksz_timer_info {int period; int /*<<< orphan*/  timer; scalar_t__ max; } ;

/* Variables and functions */
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,void (*) (struct timer_list*),int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ksz_init_timer(struct ksz_timer_info *info, int period,
	void (*function)(struct timer_list *))
{
	info->max = 0;
	info->period = period;
	timer_setup(&info->timer, function, 0);
}