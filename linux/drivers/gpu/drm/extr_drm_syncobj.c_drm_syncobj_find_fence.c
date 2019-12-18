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
typedef  int /*<<< orphan*/  wait ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ next; } ;
struct syncobj_wait_entry {TYPE_1__ node; struct dma_fence* fence; scalar_t__ point; int /*<<< orphan*/  task; } ;
struct drm_syncobj {int dummy; } ;
struct drm_file {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT ; 
 int /*<<< orphan*/  DRM_SYNCOBJ_WAIT_FOR_SUBMIT_TIMEOUT ; 
 int EINVAL ; 
 int ENOENT ; 
 int ERESTARTSYS ; 
 int ETIME ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int dma_fence_chain_find_seqno (struct dma_fence**,scalar_t__) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  drm_syncobj_fence_add_wait (struct drm_syncobj*,struct syncobj_wait_entry*) ; 
 struct dma_fence* drm_syncobj_fence_get (struct drm_syncobj*) ; 
 struct drm_syncobj* drm_syncobj_find (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 
 int /*<<< orphan*/  drm_syncobj_remove_wait (struct drm_syncobj*,struct syncobj_wait_entry*) ; 
 int /*<<< orphan*/  memset (struct syncobj_wait_entry*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nsecs_to_jiffies64 (int /*<<< orphan*/ ) ; 
 scalar_t__ schedule_timeout (scalar_t__) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

int drm_syncobj_find_fence(struct drm_file *file_private,
			   u32 handle, u64 point, u64 flags,
			   struct dma_fence **fence)
{
	struct drm_syncobj *syncobj = drm_syncobj_find(file_private, handle);
	struct syncobj_wait_entry wait;
	u64 timeout = nsecs_to_jiffies64(DRM_SYNCOBJ_WAIT_FOR_SUBMIT_TIMEOUT);
	int ret;

	if (!syncobj)
		return -ENOENT;

	*fence = drm_syncobj_fence_get(syncobj);
	drm_syncobj_put(syncobj);

	if (*fence) {
		ret = dma_fence_chain_find_seqno(fence, point);
		if (!ret)
			return 0;
		dma_fence_put(*fence);
	} else {
		ret = -EINVAL;
	}

	if (!(flags & DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT))
		return ret;

	memset(&wait, 0, sizeof(wait));
	wait.task = current;
	wait.point = point;
	drm_syncobj_fence_add_wait(syncobj, &wait);

	do {
		set_current_state(TASK_INTERRUPTIBLE);
		if (wait.fence) {
			ret = 0;
			break;
		}
                if (timeout == 0) {
                        ret = -ETIME;
                        break;
                }

		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			break;
		}

                timeout = schedule_timeout(timeout);
	} while (1);

	__set_current_state(TASK_RUNNING);
	*fence = wait.fence;

	if (wait.node.next)
		drm_syncobj_remove_wait(syncobj, &wait);

	return ret;
}