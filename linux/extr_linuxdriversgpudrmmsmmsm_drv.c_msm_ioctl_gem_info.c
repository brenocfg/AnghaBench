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
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_msm_gem_info {int flags; int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int MSM_INFO_FLAGS ; 
 int MSM_INFO_IOVA ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  msm_gem_mmap_offset (struct drm_gem_object*) ; 
 int msm_ioctl_gem_info_iova (struct drm_device*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msm_ioctl_gem_info(struct drm_device *dev, void *data,
		struct drm_file *file)
{
	struct drm_msm_gem_info *args = data;
	struct drm_gem_object *obj;
	int ret = 0;

	if (args->flags & ~MSM_INFO_FLAGS)
		return -EINVAL;

	obj = drm_gem_object_lookup(file, args->handle);
	if (!obj)
		return -ENOENT;

	if (args->flags & MSM_INFO_IOVA) {
		uint64_t iova;

		ret = msm_ioctl_gem_info_iova(dev, obj, &iova);
		if (!ret)
			args->offset = iova;
	} else {
		args->offset = msm_gem_mmap_offset(obj);
	}

	drm_gem_object_put_unlocked(obj);

	return ret;
}