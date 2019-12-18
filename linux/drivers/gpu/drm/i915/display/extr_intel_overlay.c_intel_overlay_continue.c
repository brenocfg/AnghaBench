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
typedef  int u32 ;
struct intel_overlay {int flip_addr; int /*<<< orphan*/  active; struct drm_i915_private* i915; } ;
struct i915_vma {int dummy; } ;
typedef  int i915_request ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOVSTA ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int*) ; 
 int MI_OVERLAY_CONTINUE ; 
 int MI_OVERLAY_FLIP ; 
 int OFC_UPDATE ; 
 int PTR_ERR (int*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int* alloc_request (struct intel_overlay*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_request_add (int*) ; 
 int /*<<< orphan*/  intel_overlay_flip_prepare (struct intel_overlay*,struct i915_vma*) ; 
 int /*<<< orphan*/  intel_ring_advance (int*,int*) ; 
 int* intel_ring_begin (int*,int) ; 

__attribute__((used)) static int intel_overlay_continue(struct intel_overlay *overlay,
				  struct i915_vma *vma,
				  bool load_polyphase_filter)
{
	struct drm_i915_private *dev_priv = overlay->i915;
	struct i915_request *rq;
	u32 flip_addr = overlay->flip_addr;
	u32 tmp, *cs;

	WARN_ON(!overlay->active);

	if (load_polyphase_filter)
		flip_addr |= OFC_UPDATE;

	/* check for underruns */
	tmp = I915_READ(DOVSTA);
	if (tmp & (1 << 17))
		DRM_DEBUG("overlay underrun, DOVSTA: %x\n", tmp);

	rq = alloc_request(overlay, NULL);
	if (IS_ERR(rq))
		return PTR_ERR(rq);

	cs = intel_ring_begin(rq, 2);
	if (IS_ERR(cs)) {
		i915_request_add(rq);
		return PTR_ERR(cs);
	}

	*cs++ = MI_OVERLAY_FLIP | MI_OVERLAY_CONTINUE;
	*cs++ = flip_addr;
	intel_ring_advance(rq, cs);

	intel_overlay_flip_prepare(overlay, vma);
	i915_request_add(rq);

	return 0;
}