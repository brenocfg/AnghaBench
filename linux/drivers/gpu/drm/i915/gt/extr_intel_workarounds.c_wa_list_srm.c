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
typedef  void* u32 ;
struct i915_wa_list {unsigned int count; struct i915_wa* list; } ;
struct i915_wa {int /*<<< orphan*/  reg; } ;
struct i915_vma {int dummy; } ;
struct i915_request {struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (void**) ; 
 int MI_SRM_LRM_GLOBAL_GTT ; 
 int MI_STORE_REGISTER_MEM ; 
 int PTR_ERR (void**) ; 
 int i915_ggtt_offset (struct i915_vma*) ; 
 void* i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,void**) ; 
 void** intel_ring_begin (struct i915_request*,int) ; 
 scalar_t__ mcr_range (struct drm_i915_private*,void*) ; 

__attribute__((used)) static int
wa_list_srm(struct i915_request *rq,
	    const struct i915_wa_list *wal,
	    struct i915_vma *vma)
{
	struct drm_i915_private *i915 = rq->i915;
	unsigned int i, count = 0;
	const struct i915_wa *wa;
	u32 srm, *cs;

	srm = MI_STORE_REGISTER_MEM | MI_SRM_LRM_GLOBAL_GTT;
	if (INTEL_GEN(i915) >= 8)
		srm++;

	for (i = 0, wa = wal->list; i < wal->count; i++, wa++) {
		if (!mcr_range(i915, i915_mmio_reg_offset(wa->reg)))
			count++;
	}

	cs = intel_ring_begin(rq, 4 * count);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	for (i = 0, wa = wal->list; i < wal->count; i++, wa++) {
		u32 offset = i915_mmio_reg_offset(wa->reg);

		if (mcr_range(i915, offset))
			continue;

		*cs++ = srm;
		*cs++ = offset;
		*cs++ = i915_ggtt_offset(vma) + sizeof(u32) * i;
		*cs++ = 0;
	}
	intel_ring_advance(rq, cs);

	return 0;
}