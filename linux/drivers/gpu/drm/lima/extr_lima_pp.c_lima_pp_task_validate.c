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
typedef  scalar_t__ u32 ;
struct lima_sched_task {struct drm_lima_m450_pp_frame* frame; } ;
struct lima_sched_pipe {scalar_t__ num_processor; scalar_t__ bcast_processor; } ;
struct drm_lima_m450_pp_frame {scalar_t__ num_pp; scalar_t__ _pad; } ;
struct drm_lima_m400_pp_frame {scalar_t__ num_pp; scalar_t__ _pad; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int lima_pp_task_validate(struct lima_sched_pipe *pipe,
				 struct lima_sched_task *task)
{
	u32 num_pp;

	if (pipe->bcast_processor) {
		struct drm_lima_m450_pp_frame *f = task->frame;

		num_pp = f->num_pp;

		if (f->_pad)
			return -EINVAL;
	} else {
		struct drm_lima_m400_pp_frame *f = task->frame;

		num_pp = f->num_pp;
	}

	if (num_pp == 0 || num_pp > pipe->num_processor)
		return -EINVAL;

	return 0;
}