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
struct intel_engine_cs {int mmio_base; TYPE_2__* i915; } ;
typedef  int i915_vma ;
typedef  int i915_request ;
struct i915_gem_context {int /*<<< orphan*/  i915; } ;
typedef  int drm_i915_gem_object ;
struct TYPE_3__ {int /*<<< orphan*/  vm; } ;
struct TYPE_4__ {TYPE_1__ ggtt; } ;

/* Variables and functions */
 int* ERR_PTR (int) ; 
 int /*<<< orphan*/  EXEC_OBJECT_WRITE ; 
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 int /*<<< orphan*/  I915_MAP_WB ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int*) ; 
 int MI_SRM_LRM_GLOBAL_GTT ; 
 int MI_STORE_REGISTER_MEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PIN_GLOBAL ; 
 int PTR_ERR (int*) ; 
 int /*<<< orphan*/  RING_FORCE_TO_NONPRIV (int const,int) ; 
 int RING_MAX_NONPRIV_SLOTS ; 
 int* i915_gem_object_create_internal (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_get (int*) ; 
 int* i915_gem_object_pin_map (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (int*) ; 
 int /*<<< orphan*/  i915_gem_object_set_active_reference (int*) ; 
 int /*<<< orphan*/  i915_gem_object_set_cache_level (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int*) ; 
 int i915_ggtt_offset (int*) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_request_add (int*) ; 
 int* i915_request_alloc (struct intel_engine_cs*,struct i915_gem_context*) ; 
 int* i915_vma_instance (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i915_vma_move_to_active (int*,int*,int /*<<< orphan*/ ) ; 
 int i915_vma_pin (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_unpin (int*) ; 
 int /*<<< orphan*/  intel_ring_advance (int*,int*) ; 
 int* intel_ring_begin (int*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_i915_gem_object *
read_nonprivs(struct i915_gem_context *ctx, struct intel_engine_cs *engine)
{
	struct drm_i915_gem_object *result;
	struct i915_request *rq;
	struct i915_vma *vma;
	const u32 base = engine->mmio_base;
	u32 srm, *cs;
	int err;
	int i;

	result = i915_gem_object_create_internal(engine->i915, PAGE_SIZE);
	if (IS_ERR(result))
		return result;

	i915_gem_object_set_cache_level(result, I915_CACHE_LLC);

	cs = i915_gem_object_pin_map(result, I915_MAP_WB);
	if (IS_ERR(cs)) {
		err = PTR_ERR(cs);
		goto err_obj;
	}
	memset(cs, 0xc5, PAGE_SIZE);
	i915_gem_object_unpin_map(result);

	vma = i915_vma_instance(result, &engine->i915->ggtt.vm, NULL);
	if (IS_ERR(vma)) {
		err = PTR_ERR(vma);
		goto err_obj;
	}

	err = i915_vma_pin(vma, 0, 0, PIN_GLOBAL);
	if (err)
		goto err_obj;

	rq = i915_request_alloc(engine, ctx);
	if (IS_ERR(rq)) {
		err = PTR_ERR(rq);
		goto err_pin;
	}

	err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);
	if (err)
		goto err_req;

	srm = MI_STORE_REGISTER_MEM | MI_SRM_LRM_GLOBAL_GTT;
	if (INTEL_GEN(ctx->i915) >= 8)
		srm++;

	cs = intel_ring_begin(rq, 4 * RING_MAX_NONPRIV_SLOTS);
	if (IS_ERR(cs)) {
		err = PTR_ERR(cs);
		goto err_req;
	}

	for (i = 0; i < RING_MAX_NONPRIV_SLOTS; i++) {
		*cs++ = srm;
		*cs++ = i915_mmio_reg_offset(RING_FORCE_TO_NONPRIV(base, i));
		*cs++ = i915_ggtt_offset(vma) + sizeof(u32) * i;
		*cs++ = 0;
	}
	intel_ring_advance(rq, cs);

	i915_gem_object_get(result);
	i915_gem_object_set_active_reference(result);

	i915_request_add(rq);
	i915_vma_unpin(vma);

	return result;

err_req:
	i915_request_add(rq);
err_pin:
	i915_vma_unpin(vma);
err_obj:
	i915_gem_object_put(result);
	return ERR_PTR(err);
}