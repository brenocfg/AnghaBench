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
struct drm_flip_task {void* data; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct drm_flip_task* kzalloc (int,int /*<<< orphan*/ ) ; 

struct drm_flip_task *drm_flip_work_allocate_task(void *data, gfp_t flags)
{
	struct drm_flip_task *task;

	task = kzalloc(sizeof(*task), flags);
	if (task)
		task->data = data;

	return task;
}