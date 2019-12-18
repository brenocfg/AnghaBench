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
struct lima_sched_task {int dummy; } ;
struct lima_sched_pipe {int frame_size; int /*<<< orphan*/  task_mmu_error; int /*<<< orphan*/  task_error; int /*<<< orphan*/  task_fini; int /*<<< orphan*/  task_run; int /*<<< orphan*/  task_validate; scalar_t__ task_slab; } ;
struct lima_device {struct lima_sched_pipe* pipe; } ;
struct drm_lima_gp_frame {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 scalar_t__ kmem_cache_create_usercopy (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lima_gp_task_error ; 
 int /*<<< orphan*/  lima_gp_task_fini ; 
 int /*<<< orphan*/  lima_gp_task_mmu_error ; 
 int /*<<< orphan*/  lima_gp_task_run ; 
 scalar_t__ lima_gp_task_slab ; 
 int /*<<< orphan*/  lima_gp_task_slab_refcnt ; 
 int /*<<< orphan*/  lima_gp_task_validate ; 
 int lima_pipe_gp ; 

int lima_gp_pipe_init(struct lima_device *dev)
{
	int frame_size = sizeof(struct drm_lima_gp_frame);
	struct lima_sched_pipe *pipe = dev->pipe + lima_pipe_gp;

	if (!lima_gp_task_slab) {
		lima_gp_task_slab = kmem_cache_create_usercopy(
			"lima_gp_task", sizeof(struct lima_sched_task) + frame_size,
			0, SLAB_HWCACHE_ALIGN, sizeof(struct lima_sched_task),
			frame_size, NULL);
		if (!lima_gp_task_slab)
			return -ENOMEM;
	}
	lima_gp_task_slab_refcnt++;

	pipe->frame_size = frame_size;
	pipe->task_slab = lima_gp_task_slab;

	pipe->task_validate = lima_gp_task_validate;
	pipe->task_run = lima_gp_task_run;
	pipe->task_fini = lima_gp_task_fini;
	pipe->task_error = lima_gp_task_error;
	pipe->task_mmu_error = lima_gp_task_mmu_error;

	return 0;
}