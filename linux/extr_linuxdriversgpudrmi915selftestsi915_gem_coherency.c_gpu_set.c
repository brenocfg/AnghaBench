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
typedef  void* u32 ;
typedef  void* i915_vma ;
typedef  void* i915_request ;
struct drm_i915_private {int /*<<< orphan*/  kernel_context; int /*<<< orphan*/ * engine; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_OBJECT_WRITE ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (void**) ; 
 int MI_MEM_VIRTUAL ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int MI_STORE_DWORD_IMM ; 
 int MI_STORE_DWORD_IMM_GEN4 ; 
 int MI_USE_GGTT ; 
 int PTR_ERR (void**) ; 
 size_t RCS ; 
 void** i915_gem_object_ggtt_pin (struct drm_i915_gem_object*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i915_gem_object_set_to_gtt_domain (struct drm_i915_gem_object*,int) ; 
 unsigned long i915_ggtt_offset (void**) ; 
 int /*<<< orphan*/  i915_request_add (void**) ; 
 void** i915_request_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i915_vma_move_to_active (void**,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_unpin (void**) ; 
 int /*<<< orphan*/  intel_ring_advance (void**,void**) ; 
 void** intel_ring_begin (void**,int) ; 
 int /*<<< orphan*/  lower_32_bits (unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (unsigned long) ; 

__attribute__((used)) static int gpu_set(struct drm_i915_gem_object *obj,
		   unsigned long offset,
		   u32 v)
{
	struct drm_i915_private *i915 = to_i915(obj->base.dev);
	struct i915_request *rq;
	struct i915_vma *vma;
	u32 *cs;
	int err;

	err = i915_gem_object_set_to_gtt_domain(obj, true);
	if (err)
		return err;

	vma = i915_gem_object_ggtt_pin(obj, NULL, 0, 0, 0);
	if (IS_ERR(vma))
		return PTR_ERR(vma);

	rq = i915_request_alloc(i915->engine[RCS], i915->kernel_context);
	if (IS_ERR(rq)) {
		i915_vma_unpin(vma);
		return PTR_ERR(rq);
	}

	cs = intel_ring_begin(rq, 4);
	if (IS_ERR(cs)) {
		i915_request_add(rq);
		i915_vma_unpin(vma);
		return PTR_ERR(cs);
	}

	if (INTEL_GEN(i915) >= 8) {
		*cs++ = MI_STORE_DWORD_IMM_GEN4 | 1 << 22;
		*cs++ = lower_32_bits(i915_ggtt_offset(vma) + offset);
		*cs++ = upper_32_bits(i915_ggtt_offset(vma) + offset);
		*cs++ = v;
	} else if (INTEL_GEN(i915) >= 4) {
		*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = 0;
		*cs++ = i915_ggtt_offset(vma) + offset;
		*cs++ = v;
	} else {
		*cs++ = MI_STORE_DWORD_IMM | MI_MEM_VIRTUAL;
		*cs++ = i915_ggtt_offset(vma) + offset;
		*cs++ = v;
		*cs++ = MI_NOOP;
	}
	intel_ring_advance(rq, cs);

	err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);
	i915_vma_unpin(vma);

	i915_request_add(rq);

	return err;
}