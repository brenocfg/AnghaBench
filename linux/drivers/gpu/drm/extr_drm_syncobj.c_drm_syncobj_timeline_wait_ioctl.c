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
struct drm_syncobj_timeline_wait {int flags; scalar_t__ count_handles; int /*<<< orphan*/  handles; } ;
struct drm_syncobj {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_SYNCOBJ_TIMELINE ; 
 int DRM_SYNCOBJ_WAIT_FLAGS_WAIT_ALL ; 
 int DRM_SYNCOBJ_WAIT_FLAGS_WAIT_AVAILABLE ; 
 int DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int drm_syncobj_array_find (struct drm_file*,int /*<<< orphan*/ ,scalar_t__,struct drm_syncobj***) ; 
 int /*<<< orphan*/  drm_syncobj_array_free (struct drm_syncobj**,scalar_t__) ; 
 int drm_syncobj_array_wait (struct drm_device*,struct drm_file*,int /*<<< orphan*/ *,struct drm_syncobj_timeline_wait*,struct drm_syncobj**,int) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

int
drm_syncobj_timeline_wait_ioctl(struct drm_device *dev, void *data,
				struct drm_file *file_private)
{
	struct drm_syncobj_timeline_wait *args = data;
	struct drm_syncobj **syncobjs;
	int ret = 0;

	if (!drm_core_check_feature(dev, DRIVER_SYNCOBJ_TIMELINE))
		return -EOPNOTSUPP;

	if (args->flags & ~(DRM_SYNCOBJ_WAIT_FLAGS_WAIT_ALL |
			    DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT |
			    DRM_SYNCOBJ_WAIT_FLAGS_WAIT_AVAILABLE))
		return -EINVAL;

	if (args->count_handles == 0)
		return -EINVAL;

	ret = drm_syncobj_array_find(file_private,
				     u64_to_user_ptr(args->handles),
				     args->count_handles,
				     &syncobjs);
	if (ret < 0)
		return ret;

	ret = drm_syncobj_array_wait(dev, file_private,
				     NULL, args, syncobjs, true);

	drm_syncobj_array_free(syncobjs, args->count_handles);

	return ret;
}