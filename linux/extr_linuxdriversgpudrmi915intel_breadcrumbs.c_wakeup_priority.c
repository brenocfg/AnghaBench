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
struct task_struct {int prio; } ;
struct intel_breadcrumbs {struct task_struct* signaler; } ;

/* Variables and functions */
 int INT_MIN ; 

__attribute__((used)) static inline int wakeup_priority(struct intel_breadcrumbs *b,
				  struct task_struct *tsk)
{
	if (tsk == b->signaler)
		return INT_MIN;
	else
		return tsk->prio;
}