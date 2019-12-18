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
struct intel_engine_cs {int /*<<< orphan*/  sseu; scalar_t__ cops; TYPE_2__* gt; } ;
struct intel_context {int /*<<< orphan*/  active; int /*<<< orphan*/  pin_mutex; int /*<<< orphan*/  signals; int /*<<< orphan*/  signal_link; int /*<<< orphan*/  ring; int /*<<< orphan*/  sseu; scalar_t__ ops; struct intel_engine_cs* engine; int /*<<< orphan*/  timeline; int /*<<< orphan*/  vm; struct i915_gem_context* gem_context; int /*<<< orphan*/  ref; } ;
struct i915_gem_context {int /*<<< orphan*/  i915; scalar_t__ timeline; scalar_t__ vm; } ;
struct TYPE_4__ {TYPE_1__* ggtt; } ;
struct TYPE_3__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SZ_16K ; 
 int /*<<< orphan*/  __intel_context_active ; 
 int /*<<< orphan*/  __intel_context_retire ; 
 int /*<<< orphan*/  __intel_context_ring_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_active_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_timeline_get (scalar_t__) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void
intel_context_init(struct intel_context *ce,
		   struct i915_gem_context *ctx,
		   struct intel_engine_cs *engine)
{
	GEM_BUG_ON(!engine->cops);

	kref_init(&ce->ref);

	ce->gem_context = ctx;
	ce->vm = i915_vm_get(ctx->vm ?: &engine->gt->ggtt->vm);
	if (ctx->timeline)
		ce->timeline = intel_timeline_get(ctx->timeline);

	ce->engine = engine;
	ce->ops = engine->cops;
	ce->sseu = engine->sseu;
	ce->ring = __intel_context_ring_size(SZ_16K);

	INIT_LIST_HEAD(&ce->signal_link);
	INIT_LIST_HEAD(&ce->signals);

	mutex_init(&ce->pin_mutex);

	i915_active_init(ctx->i915, &ce->active,
			 __intel_context_active, __intel_context_retire);
}