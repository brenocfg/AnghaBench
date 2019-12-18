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
struct sg_table {int dummy; } ;
struct panfrost_gem_object {int noexec; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {int dummy; } ;
struct dma_buf_attachment {int dummy; } ;

/* Variables and functions */
 struct drm_gem_object* ERR_CAST (struct drm_gem_object*) ; 
 scalar_t__ IS_ERR (struct drm_gem_object*) ; 
 struct drm_gem_object* drm_gem_shmem_prime_import_sg_table (struct drm_device*,struct dma_buf_attachment*,struct sg_table*) ; 
 struct panfrost_gem_object* to_panfrost_bo (struct drm_gem_object*) ; 

struct drm_gem_object *
panfrost_gem_prime_import_sg_table(struct drm_device *dev,
				   struct dma_buf_attachment *attach,
				   struct sg_table *sgt)
{
	struct drm_gem_object *obj;
	struct panfrost_gem_object *bo;

	obj = drm_gem_shmem_prime_import_sg_table(dev, attach, sgt);
	if (IS_ERR(obj))
		return ERR_CAST(obj);

	bo = to_panfrost_bo(obj);
	bo->noexec = true;

	return obj;
}