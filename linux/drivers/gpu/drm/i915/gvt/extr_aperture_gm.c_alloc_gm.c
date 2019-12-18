#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct drm_mm_node {int dummy; } ;
struct TYPE_4__ {struct drm_mm_node low_gm_node; struct drm_mm_node high_gm_node; } ;
struct intel_vgpu {TYPE_1__ gm; struct intel_gvt* gvt; } ;
struct intel_gvt {struct drm_i915_private* dev_priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  vm; } ;
struct drm_i915_private {TYPE_3__ drm; TYPE_2__ ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_COLOR_UNEVICTABLE ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE ; 
 unsigned int PIN_HIGH ; 
 unsigned int PIN_MAPPABLE ; 
 int /*<<< orphan*/  gvt_aperture_gmadr_base (struct intel_gvt*) ; 
 int /*<<< orphan*/  gvt_aperture_gmadr_end (struct intel_gvt*) ; 
 int /*<<< orphan*/  gvt_err (char*,char*) ; 
 int /*<<< orphan*/  gvt_hidden_gmadr_base (struct intel_gvt*) ; 
 int /*<<< orphan*/  gvt_hidden_gmadr_end (struct intel_gvt*) ; 
 int i915_gem_gtt_insert (int /*<<< orphan*/ *,struct drm_mm_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mmio_hw_access_post (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mmio_hw_access_pre (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgpu_aperture_sz (struct intel_vgpu*) ; 
 int /*<<< orphan*/  vgpu_hidden_sz (struct intel_vgpu*) ; 

__attribute__((used)) static int alloc_gm(struct intel_vgpu *vgpu, bool high_gm)
{
	struct intel_gvt *gvt = vgpu->gvt;
	struct drm_i915_private *dev_priv = gvt->dev_priv;
	unsigned int flags;
	u64 start, end, size;
	struct drm_mm_node *node;
	int ret;

	if (high_gm) {
		node = &vgpu->gm.high_gm_node;
		size = vgpu_hidden_sz(vgpu);
		start = ALIGN(gvt_hidden_gmadr_base(gvt), I915_GTT_PAGE_SIZE);
		end = ALIGN(gvt_hidden_gmadr_end(gvt), I915_GTT_PAGE_SIZE);
		flags = PIN_HIGH;
	} else {
		node = &vgpu->gm.low_gm_node;
		size = vgpu_aperture_sz(vgpu);
		start = ALIGN(gvt_aperture_gmadr_base(gvt), I915_GTT_PAGE_SIZE);
		end = ALIGN(gvt_aperture_gmadr_end(gvt), I915_GTT_PAGE_SIZE);
		flags = PIN_MAPPABLE;
	}

	mutex_lock(&dev_priv->drm.struct_mutex);
	mmio_hw_access_pre(dev_priv);
	ret = i915_gem_gtt_insert(&dev_priv->ggtt.vm, node,
				  size, I915_GTT_PAGE_SIZE,
				  I915_COLOR_UNEVICTABLE,
				  start, end, flags);
	mmio_hw_access_post(dev_priv);
	mutex_unlock(&dev_priv->drm.struct_mutex);
	if (ret)
		gvt_err("fail to alloc %s gm space from host\n",
			high_gm ? "high" : "low");

	return ret;
}