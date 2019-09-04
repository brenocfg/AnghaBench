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
struct intel_engine_cs {scalar_t__ buffer; scalar_t__ context_size; } ;
struct intel_context {scalar_t__ pin_count; scalar_t__ ring; int /*<<< orphan*/  gem_context; struct i915_vma* state; } ;
struct i915_vma {int dummy; } ;
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 struct intel_context* ERR_PTR (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int PTR_ERR (struct i915_vma*) ; 
 int __context_pin (struct intel_context*) ; 
 int __context_pin_ppgtt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __context_unpin (struct intel_context*) ; 
 struct i915_vma* alloc_context_vma (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  i915_gem_context_get (struct i915_gem_context*) ; 

__attribute__((used)) static struct intel_context *
__ring_context_pin(struct intel_engine_cs *engine,
		   struct i915_gem_context *ctx,
		   struct intel_context *ce)
{
	int err;

	if (!ce->state && engine->context_size) {
		struct i915_vma *vma;

		vma = alloc_context_vma(engine);
		if (IS_ERR(vma)) {
			err = PTR_ERR(vma);
			goto err;
		}

		ce->state = vma;
	}

	err = __context_pin(ce);
	if (err)
		goto err;

	err = __context_pin_ppgtt(ce->gem_context);
	if (err)
		goto err_unpin;

	i915_gem_context_get(ctx);

	/* One ringbuffer to rule them all */
	GEM_BUG_ON(!engine->buffer);
	ce->ring = engine->buffer;

	return ce;

err_unpin:
	__context_unpin(ce);
err:
	ce->pin_count = 0;
	return ERR_PTR(err);
}