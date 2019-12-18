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
struct TYPE_2__ {int /*<<< orphan*/  madv_list; } ;
struct panfrost_gem_object {TYPE_1__ base; } ;
struct panfrost_device {int /*<<< orphan*/  shrinker_lock; int /*<<< orphan*/  shrinker_list; } ;
struct drm_panfrost_madvise {scalar_t__ madv; scalar_t__ retained; int /*<<< orphan*/  handle; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct panfrost_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 scalar_t__ PANFROST_MADV_DONTNEED ; 
 scalar_t__ PANFROST_MADV_WILLNEED ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 scalar_t__ drm_gem_shmem_madvise (struct drm_gem_object*,scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct panfrost_gem_object* to_panfrost_bo (struct drm_gem_object*) ; 

__attribute__((used)) static int panfrost_ioctl_madvise(struct drm_device *dev, void *data,
				  struct drm_file *file_priv)
{
	struct drm_panfrost_madvise *args = data;
	struct panfrost_device *pfdev = dev->dev_private;
	struct drm_gem_object *gem_obj;

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	if (!gem_obj) {
		DRM_DEBUG("Failed to look up GEM BO %d\n", args->handle);
		return -ENOENT;
	}

	args->retained = drm_gem_shmem_madvise(gem_obj, args->madv);

	if (args->retained) {
		struct panfrost_gem_object *bo = to_panfrost_bo(gem_obj);

		mutex_lock(&pfdev->shrinker_lock);

		if (args->madv == PANFROST_MADV_DONTNEED)
			list_add_tail(&bo->base.madv_list, &pfdev->shrinker_list);
		else if (args->madv == PANFROST_MADV_WILLNEED)
			list_del_init(&bo->base.madv_list);

		mutex_unlock(&pfdev->shrinker_lock);
	}

	drm_gem_object_put_unlocked(gem_obj);
	return 0;
}