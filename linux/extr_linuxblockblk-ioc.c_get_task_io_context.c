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
struct task_struct {struct io_context* io_context; } ;
struct io_context {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  create_task_io_context (struct task_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_io_context (struct io_context*) ; 
 int /*<<< orphan*/  gfpflags_allow_blocking (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct io_context*) ; 
 int /*<<< orphan*/  might_sleep_if (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

struct io_context *get_task_io_context(struct task_struct *task,
				       gfp_t gfp_flags, int node)
{
	struct io_context *ioc;

	might_sleep_if(gfpflags_allow_blocking(gfp_flags));

	do {
		task_lock(task);
		ioc = task->io_context;
		if (likely(ioc)) {
			get_io_context(ioc);
			task_unlock(task);
			return ioc;
		}
		task_unlock(task);
	} while (!create_task_io_context(task, gfp_flags, node));

	return NULL;
}