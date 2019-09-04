#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {scalar_t__ mm; TYPE_1__* group_leader; } ;
struct kfd_process {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct kfd_process* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct kfd_process* create_process (struct task_struct*,struct file*) ; 
 struct task_struct* current ; 
 struct kfd_process* find_process (struct task_struct*) ; 
 int /*<<< orphan*/  kfd_processes_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

struct kfd_process *kfd_create_process(struct file *filep)
{
	struct kfd_process *process;
	struct task_struct *thread = current;

	if (!thread->mm)
		return ERR_PTR(-EINVAL);

	/* Only the pthreads threading model is supported. */
	if (thread->group_leader->mm != thread->mm)
		return ERR_PTR(-EINVAL);

	/*
	 * take kfd processes mutex before starting of process creation
	 * so there won't be a case where two threads of the same process
	 * create two kfd_process structures
	 */
	mutex_lock(&kfd_processes_mutex);

	/* A prior open of /dev/kfd could have already created the process. */
	process = find_process(thread);
	if (process)
		pr_debug("Process already found\n");
	else
		process = create_process(thread, filep);

	mutex_unlock(&kfd_processes_mutex);

	return process;
}