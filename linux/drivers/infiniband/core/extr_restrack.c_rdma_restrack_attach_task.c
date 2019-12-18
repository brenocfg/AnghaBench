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
struct rdma_restrack_entry {struct task_struct* task; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 

void rdma_restrack_attach_task(struct rdma_restrack_entry *res,
			       struct task_struct *task)
{
	if (res->task)
		put_task_struct(res->task);
	get_task_struct(task);
	res->task = task;
}