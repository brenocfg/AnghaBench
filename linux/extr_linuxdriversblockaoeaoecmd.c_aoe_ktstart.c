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
struct ktstate {int /*<<< orphan*/  rendez; struct task_struct* task; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct ktstate*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
aoe_ktstart(struct ktstate *k)
{
	struct task_struct *task;

	init_completion(&k->rendez);
	task = kthread_run(kthread, k, "%s", k->name);
	if (task == NULL || IS_ERR(task))
		return -ENOMEM;
	k->task = task;
	wait_for_completion(&k->rendez); /* allow kthread to start */
	init_completion(&k->rendez);	/* for waiting for exit later */
	return 0;
}