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
struct task_ipc {void* in; void* out; int /*<<< orphan*/  work; scalar_t__ value; int /*<<< orphan*/  started; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK_ONSTACK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ READ_ONCE (scalar_t__) ; 
 void* alloc_fence () ; 
 int /*<<< orphan*/  destroy_work_on_stack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_fence (void*) ; 
 int /*<<< orphan*/  i915_sw_fence_commit (void*) ; 
 int /*<<< orphan*/  i915_sw_fence_wait (void*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_ipc ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_ipc(void *arg)
{
	struct task_ipc ipc;
	int ret = 0;

	/* Test use of i915_sw_fence as an interprocess signaling mechanism */
	ipc.in = alloc_fence();
	if (!ipc.in)
		return -ENOMEM;
	ipc.out = alloc_fence();
	if (!ipc.out) {
		ret = -ENOMEM;
		goto err_in;
	}

	/* use a completion to avoid chicken-and-egg testing */
	init_completion(&ipc.started);

	ipc.value = 0;
	INIT_WORK_ONSTACK(&ipc.work, task_ipc);
	schedule_work(&ipc.work);

	wait_for_completion(&ipc.started);

	usleep_range(1000, 2000);
	if (READ_ONCE(ipc.value)) {
		pr_err("worker updated value before i915_sw_fence was signaled\n");
		ret = -EINVAL;
	}

	i915_sw_fence_commit(ipc.in);
	i915_sw_fence_wait(ipc.out);

	if (!READ_ONCE(ipc.value)) {
		pr_err("worker signaled i915_sw_fence before value was posted\n");
		ret = -EINVAL;
	}

	flush_work(&ipc.work);
	destroy_work_on_stack(&ipc.work);
	free_fence(ipc.out);
err_in:
	free_fence(ipc.in);
	return ret;
}