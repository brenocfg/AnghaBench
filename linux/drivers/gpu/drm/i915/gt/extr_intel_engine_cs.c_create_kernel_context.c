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
struct intel_engine_cs {TYPE_1__* i915; } ;
struct intel_context {int /*<<< orphan*/  ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  kernel_context; } ;

/* Variables and functions */
 struct intel_context* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct intel_context*) ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  __intel_context_ring_size (int /*<<< orphan*/ ) ; 
 struct intel_context* intel_context_create (int /*<<< orphan*/ ,struct intel_engine_cs*) ; 
 int intel_context_pin (struct intel_context*) ; 
 int /*<<< orphan*/  intel_context_put (struct intel_context*) ; 

__attribute__((used)) static struct intel_context *
create_kernel_context(struct intel_engine_cs *engine)
{
	struct intel_context *ce;
	int err;

	ce = intel_context_create(engine->i915->kernel_context, engine);
	if (IS_ERR(ce))
		return ce;

	ce->ring = __intel_context_ring_size(SZ_4K);

	err = intel_context_pin(ce);
	if (err) {
		intel_context_put(ce);
		return ERR_PTR(err);
	}

	return ce;
}