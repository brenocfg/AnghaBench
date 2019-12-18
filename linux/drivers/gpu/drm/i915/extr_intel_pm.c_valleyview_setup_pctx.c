#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int start; } ;
struct drm_i915_private {struct drm_i915_gem_object* vlv_pctx; TYPE_1__ dsm; } ;
struct drm_i915_gem_object {TYPE_2__* stolen; } ;
typedef  int resource_size_t ;
struct TYPE_4__ {int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_GTT_OFFSET_NONE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  VLV_PCBR ; 
 struct drm_i915_gem_object* i915_gem_object_create_stolen (struct drm_i915_private*,int) ; 
 struct drm_i915_gem_object* i915_gem_object_create_stolen_for_preallocated (struct drm_i915_private*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  range_overflows_t (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64 ; 

__attribute__((used)) static void valleyview_setup_pctx(struct drm_i915_private *dev_priv)
{
	struct drm_i915_gem_object *pctx;
	resource_size_t pctx_paddr;
	resource_size_t pctx_size = 24*1024;
	u32 pcbr;

	pcbr = I915_READ(VLV_PCBR);
	if (pcbr) {
		/* BIOS set it up already, grab the pre-alloc'd space */
		resource_size_t pcbr_offset;

		pcbr_offset = (pcbr & (~4095)) - dev_priv->dsm.start;
		pctx = i915_gem_object_create_stolen_for_preallocated(dev_priv,
								      pcbr_offset,
								      I915_GTT_OFFSET_NONE,
								      pctx_size);
		goto out;
	}

	DRM_DEBUG_DRIVER("BIOS didn't set up PCBR, fixing up\n");

	/*
	 * From the Gunit register HAS:
	 * The Gfx driver is expected to program this register and ensure
	 * proper allocation within Gfx stolen memory.  For example, this
	 * register should be programmed such than the PCBR range does not
	 * overlap with other ranges, such as the frame buffer, protected
	 * memory, or any other relevant ranges.
	 */
	pctx = i915_gem_object_create_stolen(dev_priv, pctx_size);
	if (!pctx) {
		DRM_DEBUG("not enough stolen space for PCTX, disabling\n");
		goto out;
	}

	GEM_BUG_ON(range_overflows_t(u64,
				     dev_priv->dsm.start,
				     pctx->stolen->start,
				     U32_MAX));
	pctx_paddr = dev_priv->dsm.start + pctx->stolen->start;
	I915_WRITE(VLV_PCBR, pctx_paddr);

out:
	DRM_DEBUG_DRIVER("PCBR: 0x%08x\n", I915_READ(VLV_PCBR));
	dev_priv->vlv_pctx = pctx;
}