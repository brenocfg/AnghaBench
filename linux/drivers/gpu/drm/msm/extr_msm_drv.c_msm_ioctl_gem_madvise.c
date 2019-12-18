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
struct drm_msm_gem_madvise {int madv; int retained; int /*<<< orphan*/  handle; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
#define  MSM_MADV_DONTNEED 129 
#define  MSM_MADV_WILLNEED 128 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put (struct drm_gem_object*) ; 
 int msm_gem_madvise (struct drm_gem_object*,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msm_ioctl_gem_madvise(struct drm_device *dev, void *data,
		struct drm_file *file)
{
	struct drm_msm_gem_madvise *args = data;
	struct drm_gem_object *obj;
	int ret;

	switch (args->madv) {
	case MSM_MADV_DONTNEED:
	case MSM_MADV_WILLNEED:
		break;
	default:
		return -EINVAL;
	}

	ret = mutex_lock_interruptible(&dev->struct_mutex);
	if (ret)
		return ret;

	obj = drm_gem_object_lookup(file, args->handle);
	if (!obj) {
		ret = -ENOENT;
		goto unlock;
	}

	ret = msm_gem_madvise(obj, args->madv);
	if (ret >= 0) {
		args->retained = ret;
		ret = 0;
	}

	drm_gem_object_put(obj);

unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}