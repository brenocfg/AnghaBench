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
struct lima_vm {int dummy; } ;
struct lima_sched_task {int num_bos; int /*<<< orphan*/  deps; int /*<<< orphan*/  vm; int /*<<< orphan*/  bos; int /*<<< orphan*/  base; } ;
struct lima_sched_context {int /*<<< orphan*/  base; } ;
struct lima_bo {int /*<<< orphan*/  gem; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  XA_FLAGS_ALLOC ; 
 int /*<<< orphan*/  drm_gem_object_get (int /*<<< orphan*/ *) ; 
 int drm_sched_job_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct lima_vm*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemdup (struct lima_bo**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_vm_get (struct lima_vm*) ; 
 int /*<<< orphan*/  xa_init_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int lima_sched_task_init(struct lima_sched_task *task,
			 struct lima_sched_context *context,
			 struct lima_bo **bos, int num_bos,
			 struct lima_vm *vm)
{
	int err, i;

	task->bos = kmemdup(bos, sizeof(*bos) * num_bos, GFP_KERNEL);
	if (!task->bos)
		return -ENOMEM;

	for (i = 0; i < num_bos; i++)
		drm_gem_object_get(&bos[i]->gem);

	err = drm_sched_job_init(&task->base, &context->base, vm);
	if (err) {
		kfree(task->bos);
		return err;
	}

	task->num_bos = num_bos;
	task->vm = lima_vm_get(vm);

	xa_init_flags(&task->deps, XA_FLAGS_ALLOC);

	return 0;
}