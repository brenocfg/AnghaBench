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
struct drm_msm_gem_cpu_prep {int op; int /*<<< orphan*/  handle; int /*<<< orphan*/  timeout; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int ENOENT ; 
 int MSM_PREP_FLAGS ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int msm_gem_cpu_prep (struct drm_gem_object*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_ktime (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msm_ioctl_gem_cpu_prep(struct drm_device *dev, void *data,
		struct drm_file *file)
{
	struct drm_msm_gem_cpu_prep *args = data;
	struct drm_gem_object *obj;
	ktime_t timeout = to_ktime(args->timeout);
	int ret;

	if (args->op & ~MSM_PREP_FLAGS) {
		DRM_ERROR("invalid op: %08x\n", args->op);
		return -EINVAL;
	}

	obj = drm_gem_object_lookup(file, args->handle);
	if (!obj)
		return -ENOENT;

	ret = msm_gem_cpu_prep(obj, args->op, &timeout);

	drm_gem_object_put_unlocked(obj);

	return ret;
}