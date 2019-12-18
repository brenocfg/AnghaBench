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
typedef  void* uint32_t ;
struct drm_syncobj_wait {void* first_signaled; int /*<<< orphan*/  flags; int /*<<< orphan*/  count_handles; int /*<<< orphan*/  timeout_nsec; } ;
struct drm_syncobj_timeline_wait {void* first_signaled; int /*<<< orphan*/  flags; int /*<<< orphan*/  count_handles; int /*<<< orphan*/  points; int /*<<< orphan*/  timeout_nsec; } ;
struct drm_syncobj {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 long drm_syncobj_array_wait_timeout (struct drm_syncobj**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,void**) ; 
 long drm_timeout_abs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * u64_to_user_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_syncobj_array_wait(struct drm_device *dev,
				  struct drm_file *file_private,
				  struct drm_syncobj_wait *wait,
				  struct drm_syncobj_timeline_wait *timeline_wait,
				  struct drm_syncobj **syncobjs, bool timeline)
{
	signed long timeout = 0;
	uint32_t first = ~0;

	if (!timeline) {
		timeout = drm_timeout_abs_to_jiffies(wait->timeout_nsec);
		timeout = drm_syncobj_array_wait_timeout(syncobjs,
							 NULL,
							 wait->count_handles,
							 wait->flags,
							 timeout, &first);
		if (timeout < 0)
			return timeout;
		wait->first_signaled = first;
	} else {
		timeout = drm_timeout_abs_to_jiffies(timeline_wait->timeout_nsec);
		timeout = drm_syncobj_array_wait_timeout(syncobjs,
							 u64_to_user_ptr(timeline_wait->points),
							 timeline_wait->count_handles,
							 timeline_wait->flags,
							 timeout, &first);
		if (timeout < 0)
			return timeout;
		timeline_wait->first_signaled = first;
	}
	return 0;
}