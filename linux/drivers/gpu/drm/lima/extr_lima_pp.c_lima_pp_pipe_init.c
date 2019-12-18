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
struct lima_device {scalar_t__ id; struct lima_sched_pipe* pipe; } ;
struct drm_lima_m450_pp_frame {int dummy; } ;
struct drm_lima_m400_pp_frame {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 scalar_t__ kmem_cache_create_usercopy (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ lima_gpu_mali400 ; 
 int lima_pipe_pp ; 
 int /*<<< orphan*/  lima_pp_task_error ; 
 int /*<<< orphan*/  lima_pp_task_fini ; 
 int /*<<< orphan*/  lima_pp_task_mmu_error ; 
 int /*<<< orphan*/  lima_pp_task_run ; 
 scalar_t__ lima_pp_task_slab ; 
 int /*<<< orphan*/  lima_pp_task_slab_refcnt ; 
 int /*<<< orphan*/  lima_pp_task_validate ; 

int lima_pp_pipe_init(struct lima_device *dev)
{
	int frame_size;
	struct lima_sched_pipe *pipe = dev->pipe + lima_pipe_pp;

	if (dev->id == lima_gpu_mali400)
		frame_size = sizeof(struct drm_lima_m400_pp_frame);
	else
		frame_size = sizeof(struct drm_lima_m450_pp_frame);

	if (!lima_pp_task_slab) {
		lima_pp_task_slab = kmem_cache_create_usercopy(
			"lima_pp_task", sizeof(struct lima_sched_task) + frame_size,
			0, SLAB_HWCACHE_ALIGN, sizeof(struct lima_sched_task),
			frame_size, NULL);
		if (!lima_pp_task_slab)
			return -ENOMEM;
	}
	lima_pp_task_slab_refcnt++;

	pipe->frame_size = frame_size;
	pipe->task_slab = lima_pp_task_slab;

	pipe->task_validate = lima_pp_task_validate;
	pipe->task_run = lima_pp_task_run;
	pipe->task_fini = lima_pp_task_fini;
	pipe->task_error = lima_pp_task_error;
	pipe->task_mmu_error = lima_pp_task_mmu_error;

	return 0;
}