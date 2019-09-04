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
struct TYPE_2__ {scalar_t__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct kfd_process* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct kfd_process* find_process (struct task_struct const*) ; 

struct kfd_process *kfd_get_process(const struct task_struct *thread)
{
	struct kfd_process *process;

	if (!thread->mm)
		return ERR_PTR(-EINVAL);

	/* Only the pthreads threading model is supported. */
	if (thread->group_leader->mm != thread->mm)
		return ERR_PTR(-EINVAL);

	process = find_process(thread);
	if (!process)
		return ERR_PTR(-EINVAL);

	return process;
}