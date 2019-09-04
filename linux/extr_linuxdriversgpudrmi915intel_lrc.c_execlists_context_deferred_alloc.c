#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct intel_ring {int dummy; } ;
struct intel_engine_cs {int /*<<< orphan*/  context_size; } ;
struct intel_context {struct intel_ring* state; struct intel_ring* ring; } ;
typedef  struct intel_ring i915_vma ;
typedef  struct intel_ring i915_timeline ;
struct i915_gem_context {int /*<<< orphan*/  ring_size; int /*<<< orphan*/  name; TYPE_2__* i915; } ;
typedef  struct intel_ring drm_i915_gem_object ;
struct TYPE_4__ {int /*<<< orphan*/  vm; } ;
struct TYPE_5__ {TYPE_1__ ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE ; 
 scalar_t__ IS_ERR (struct intel_ring*) ; 
 int LRC_HEADER_PAGES ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct intel_ring*) ; 
 struct intel_ring* i915_gem_object_create (TYPE_2__*,int) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct intel_ring*) ; 
 struct intel_ring* i915_timeline_create (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_timeline_put (struct intel_ring*) ; 
 struct intel_ring* i915_vma_instance (struct intel_ring*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct intel_ring* intel_engine_create_ring (struct intel_engine_cs*,struct intel_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_free (struct intel_ring*) ; 
 int populate_lr_context (struct i915_gem_context*,struct intel_ring*,struct intel_engine_cs*,struct intel_ring*) ; 
 int round_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int execlists_context_deferred_alloc(struct i915_gem_context *ctx,
					    struct intel_engine_cs *engine,
					    struct intel_context *ce)
{
	struct drm_i915_gem_object *ctx_obj;
	struct i915_vma *vma;
	uint32_t context_size;
	struct intel_ring *ring;
	struct i915_timeline *timeline;
	int ret;

	if (ce->state)
		return 0;

	context_size = round_up(engine->context_size, I915_GTT_PAGE_SIZE);

	/*
	 * Before the actual start of the context image, we insert a few pages
	 * for our own use and for sharing with the GuC.
	 */
	context_size += LRC_HEADER_PAGES * PAGE_SIZE;

	ctx_obj = i915_gem_object_create(ctx->i915, context_size);
	if (IS_ERR(ctx_obj))
		return PTR_ERR(ctx_obj);

	vma = i915_vma_instance(ctx_obj, &ctx->i915->ggtt.vm, NULL);
	if (IS_ERR(vma)) {
		ret = PTR_ERR(vma);
		goto error_deref_obj;
	}

	timeline = i915_timeline_create(ctx->i915, ctx->name);
	if (IS_ERR(timeline)) {
		ret = PTR_ERR(timeline);
		goto error_deref_obj;
	}

	ring = intel_engine_create_ring(engine, timeline, ctx->ring_size);
	i915_timeline_put(timeline);
	if (IS_ERR(ring)) {
		ret = PTR_ERR(ring);
		goto error_deref_obj;
	}

	ret = populate_lr_context(ctx, ctx_obj, engine, ring);
	if (ret) {
		DRM_DEBUG_DRIVER("Failed to populate LRC: %d\n", ret);
		goto error_ring_free;
	}

	ce->ring = ring;
	ce->state = vma;

	return 0;

error_ring_free:
	intel_ring_free(ring);
error_deref_obj:
	i915_gem_object_put(ctx_obj);
	return ret;
}