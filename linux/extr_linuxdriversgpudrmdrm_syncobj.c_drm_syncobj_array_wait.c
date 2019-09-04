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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_syncobj_wait {int /*<<< orphan*/  first_signaled; int /*<<< orphan*/  flags; int /*<<< orphan*/  count_handles; int /*<<< orphan*/  timeout_nsec; } ;
struct drm_syncobj {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ETIME ; 
 long drm_syncobj_array_wait_timeout (struct drm_syncobj**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ *) ; 
 long drm_timeout_abs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_syncobj_array_wait(struct drm_device *dev,
				  struct drm_file *file_private,
				  struct drm_syncobj_wait *wait,
				  struct drm_syncobj **syncobjs)
{
	signed long timeout = drm_timeout_abs_to_jiffies(wait->timeout_nsec);
	signed long ret = 0;
	uint32_t first = ~0;

	ret = drm_syncobj_array_wait_timeout(syncobjs,
					     wait->count_handles,
					     wait->flags,
					     timeout, &first);
	if (ret < 0)
		return ret;

	wait->first_signaled = first;
	if (ret == 0)
		return -ETIME;
	return 0;
}