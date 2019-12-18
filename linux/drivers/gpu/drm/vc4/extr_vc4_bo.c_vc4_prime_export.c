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
struct vc4_bo {scalar_t__ validated_shader; } ;
struct drm_gem_object {int dummy; } ;
struct dma_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 struct dma_buf* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct dma_buf*) ; 
 struct dma_buf* drm_gem_prime_export (struct drm_gem_object*,int) ; 
 struct vc4_bo* to_vc4_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vc4_bo_dec_usecnt (struct vc4_bo*) ; 
 int vc4_bo_inc_usecnt (struct vc4_bo*) ; 

struct dma_buf * vc4_prime_export(struct drm_gem_object *obj, int flags)
{
	struct vc4_bo *bo = to_vc4_bo(obj);
	struct dma_buf *dmabuf;
	int ret;

	if (bo->validated_shader) {
		DRM_DEBUG("Attempting to export shader BO\n");
		return ERR_PTR(-EINVAL);
	}

	/* Note: as soon as the BO is exported it becomes unpurgeable, because
	 * noone ever decrements the usecnt even if the reference held by the
	 * exported BO is released. This shouldn't be a problem since we don't
	 * expect exported BOs to be marked as purgeable.
	 */
	ret = vc4_bo_inc_usecnt(bo);
	if (ret) {
		DRM_ERROR("Failed to increment BO usecnt\n");
		return ERR_PTR(ret);
	}

	dmabuf = drm_gem_prime_export(obj, flags);
	if (IS_ERR(dmabuf))
		vc4_bo_dec_usecnt(bo);

	return dmabuf;
}