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
struct pid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PGID ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 struct task_struct* pid_task (struct pid*,int /*<<< orphan*/ ) ; 
 struct pid* task_session (struct task_struct*) ; 

__attribute__((used)) static struct pid *session_of_pgrp(struct pid *pgrp)
{
	struct task_struct *p;
	struct pid *sid = NULL;

	p = pid_task(pgrp, PIDTYPE_PGID);
	if (p == NULL)
		p = pid_task(pgrp, PIDTYPE_PID);
	if (p != NULL)
		sid = task_session(p);

	return sid;
}