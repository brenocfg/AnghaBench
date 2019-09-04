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
struct intel_engine_cs {int dummy; } ;
typedef  void i915_request ;
struct hang {void* obj; int /*<<< orphan*/  ctx; void* batch; int /*<<< orphan*/  i915; } ;
typedef  void drm_i915_gem_object ;

/* Variables and functions */
 void* ERR_CAST (void*) ; 
 void* ERR_PTR (int) ; 
 scalar_t__ HAS_LLC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_MAP_WB ; 
 int /*<<< orphan*/  I915_MAP_WC ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int emit_recurse_batch (struct hang*,void*) ; 
 void* i915_gem_object_create_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i915_gem_object_is_active (void*) ; 
 void* i915_gem_object_pin_map (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (void*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (void*) ; 
 int /*<<< orphan*/  i915_request_add (void*) ; 
 void* i915_request_alloc (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct i915_request *
hang_create_request(struct hang *h, struct intel_engine_cs *engine)
{
	struct i915_request *rq;
	int err;

	if (i915_gem_object_is_active(h->obj)) {
		struct drm_i915_gem_object *obj;
		void *vaddr;

		obj = i915_gem_object_create_internal(h->i915, PAGE_SIZE);
		if (IS_ERR(obj))
			return ERR_CAST(obj);

		vaddr = i915_gem_object_pin_map(obj,
						HAS_LLC(h->i915) ? I915_MAP_WB : I915_MAP_WC);
		if (IS_ERR(vaddr)) {
			i915_gem_object_put(obj);
			return ERR_CAST(vaddr);
		}

		i915_gem_object_unpin_map(h->obj);
		i915_gem_object_put(h->obj);

		h->obj = obj;
		h->batch = vaddr;
	}

	rq = i915_request_alloc(engine, h->ctx);
	if (IS_ERR(rq))
		return rq;

	err = emit_recurse_batch(h, rq);
	if (err) {
		i915_request_add(rq);
		return ERR_PTR(err);
	}

	return rq;
}