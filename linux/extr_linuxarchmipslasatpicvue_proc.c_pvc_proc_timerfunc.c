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
struct timer_list {int dummy; } ;
struct TYPE_3__ {scalar_t__ expires; } ;

/* Variables and functions */
 int DISPLAY ; 
 int LEFT ; 
 int RIGHT ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  pvc_move (int) ; 
 scalar_t__ scroll_dir ; 
 scalar_t__ scroll_interval ; 
 TYPE_1__ timer ; 

void pvc_proc_timerfunc(struct timer_list *unused)
{
	if (scroll_dir < 0)
		pvc_move(DISPLAY|RIGHT);
	else if (scroll_dir > 0)
		pvc_move(DISPLAY|LEFT);

	timer.expires = jiffies + scroll_interval;
	add_timer(&timer);
}