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
struct etnaviv_gem_submit {unsigned int nr_bos; TYPE_1__* bos; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int /*<<< orphan*/  table_lock; int /*<<< orphan*/  object_idr; } ;
struct drm_etnaviv_gem_submit_bo {int flags; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int BO_INVALID_FLAGS ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_gem_object_get (struct drm_gem_object*) ; 
 struct drm_gem_object* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_etnaviv_bo (struct drm_gem_object*) ; 

__attribute__((used)) static int submit_lookup_objects(struct etnaviv_gem_submit *submit,
	struct drm_file *file, struct drm_etnaviv_gem_submit_bo *submit_bos,
	unsigned nr_bos)
{
	struct drm_etnaviv_gem_submit_bo *bo;
	unsigned i;
	int ret = 0;

	spin_lock(&file->table_lock);

	for (i = 0, bo = submit_bos; i < nr_bos; i++, bo++) {
		struct drm_gem_object *obj;

		if (bo->flags & BO_INVALID_FLAGS) {
			DRM_ERROR("invalid flags: %x\n", bo->flags);
			ret = -EINVAL;
			goto out_unlock;
		}

		submit->bos[i].flags = bo->flags;

		/* normally use drm_gem_object_lookup(), but for bulk lookup
		 * all under single table_lock just hit object_idr directly:
		 */
		obj = idr_find(&file->object_idr, bo->handle);
		if (!obj) {
			DRM_ERROR("invalid handle %u at index %u\n",
				  bo->handle, i);
			ret = -EINVAL;
			goto out_unlock;
		}

		/*
		 * Take a refcount on the object. The file table lock
		 * prevents the object_idr's refcount on this being dropped.
		 */
		drm_gem_object_get(obj);

		submit->bos[i].obj = to_etnaviv_bo(obj);
	}

out_unlock:
	submit->nr_bos = i;
	spin_unlock(&file->table_lock);

	return ret;
}