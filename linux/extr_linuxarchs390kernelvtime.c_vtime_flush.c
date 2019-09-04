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
struct task_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ do_account_vtime (struct task_struct*) ; 
 int /*<<< orphan*/  virt_timer_expire () ; 

void vtime_flush(struct task_struct *tsk)
{
	if (do_account_vtime(tsk))
		virt_timer_expire();
}