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
struct intel_context {int dummy; } ;
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct intel_context* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct intel_context* intel_context_alloc () ; 
 int /*<<< orphan*/  intel_context_init (struct intel_context*,struct i915_gem_context*,struct intel_engine_cs*) ; 

struct intel_context *
intel_context_create(struct i915_gem_context *ctx,
		     struct intel_engine_cs *engine)
{
	struct intel_context *ce;

	ce = intel_context_alloc();
	if (!ce)
		return ERR_PTR(-ENOMEM);

	intel_context_init(ce, ctx, engine);
	return ce;
}