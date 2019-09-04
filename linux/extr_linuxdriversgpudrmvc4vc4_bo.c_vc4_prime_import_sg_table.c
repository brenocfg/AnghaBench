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
struct vc4_bo {int /*<<< orphan*/  resv; } ;
struct sg_table {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {int dummy; } ;
struct dma_buf_attachment {TYPE_1__* dmabuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  resv; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_gem_object*) ; 
 struct drm_gem_object* drm_gem_cma_prime_import_sg_table (struct drm_device*,struct dma_buf_attachment*,struct sg_table*) ; 
 struct vc4_bo* to_vc4_bo (struct drm_gem_object*) ; 

struct drm_gem_object *
vc4_prime_import_sg_table(struct drm_device *dev,
			  struct dma_buf_attachment *attach,
			  struct sg_table *sgt)
{
	struct drm_gem_object *obj;
	struct vc4_bo *bo;

	obj = drm_gem_cma_prime_import_sg_table(dev, attach, sgt);
	if (IS_ERR(obj))
		return obj;

	bo = to_vc4_bo(obj);
	bo->resv = attach->dmabuf->resv;

	return obj;
}