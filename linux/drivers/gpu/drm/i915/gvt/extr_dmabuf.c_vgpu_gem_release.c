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
struct intel_vgpu_fb_info {struct intel_vgpu_dmabuf_obj* obj; } ;
struct intel_vgpu_dmabuf_obj {struct intel_vgpu* vgpu; } ;
struct intel_vgpu {int /*<<< orphan*/  dmabuf_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dma_buf; } ;
struct drm_i915_gem_object {TYPE_1__ base; struct intel_vgpu_fb_info* gvt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmabuf_obj_put (struct intel_vgpu_dmabuf_obj*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vgpu_gem_release(struct drm_i915_gem_object *gem_obj)
{

	struct intel_vgpu_fb_info *fb_info = gem_obj->gvt_info;
	struct intel_vgpu_dmabuf_obj *obj = fb_info->obj;
	struct intel_vgpu *vgpu = obj->vgpu;

	if (vgpu) {
		mutex_lock(&vgpu->dmabuf_lock);
		gem_obj->base.dma_buf = NULL;
		dmabuf_obj_put(obj);
		mutex_unlock(&vgpu->dmabuf_lock);
	} else {
		/* vgpu is NULL, as it has been removed already */
		gem_obj->base.dma_buf = NULL;
		dmabuf_obj_put(obj);
	}
}