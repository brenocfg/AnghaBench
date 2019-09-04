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
struct drm_flip_work {int /*<<< orphan*/  (* func ) (struct drm_flip_work*,void*) ;int /*<<< orphan*/  name; } ;
struct drm_flip_task {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ drm_can_sleep () ; 
 struct drm_flip_task* drm_flip_work_allocate_task (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_flip_work_queue_task (struct drm_flip_work*,struct drm_flip_task*) ; 
 int /*<<< orphan*/  stub1 (struct drm_flip_work*,void*) ; 

void drm_flip_work_queue(struct drm_flip_work *work, void *val)
{
	struct drm_flip_task *task;

	task = drm_flip_work_allocate_task(val,
				drm_can_sleep() ? GFP_KERNEL : GFP_ATOMIC);
	if (task) {
		drm_flip_work_queue_task(work, task);
	} else {
		DRM_ERROR("%s could not allocate task!\n", work->name);
		work->func(work, val);
	}
}