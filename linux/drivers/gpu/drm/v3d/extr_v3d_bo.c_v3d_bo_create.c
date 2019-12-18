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
struct v3d_bo {int dummy; } ;
struct drm_gem_shmem_object {int /*<<< orphan*/  base; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct v3d_bo* ERR_CAST (struct drm_gem_shmem_object*) ; 
 struct v3d_bo* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct drm_gem_shmem_object*) ; 
 struct drm_gem_shmem_object* drm_gem_shmem_create (struct drm_device*,size_t) ; 
 int /*<<< orphan*/  drm_gem_shmem_free_object (int /*<<< orphan*/ *) ; 
 struct v3d_bo* to_v3d_bo (int /*<<< orphan*/ *) ; 
 int v3d_bo_create_finish (int /*<<< orphan*/ *) ; 

struct v3d_bo *v3d_bo_create(struct drm_device *dev, struct drm_file *file_priv,
			     size_t unaligned_size)
{
	struct drm_gem_shmem_object *shmem_obj;
	struct v3d_bo *bo;
	int ret;

	shmem_obj = drm_gem_shmem_create(dev, unaligned_size);
	if (IS_ERR(shmem_obj))
		return ERR_CAST(shmem_obj);
	bo = to_v3d_bo(&shmem_obj->base);

	ret = v3d_bo_create_finish(&shmem_obj->base);
	if (ret)
		goto free_obj;

	return bo;

free_obj:
	drm_gem_shmem_free_object(&shmem_obj->base);
	return ERR_PTR(ret);
}