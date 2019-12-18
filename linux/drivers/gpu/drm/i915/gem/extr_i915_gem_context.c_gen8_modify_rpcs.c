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
struct intel_sseu {int dummy; } ;
struct intel_context {TYPE_1__* engine; int /*<<< orphan*/  pin_mutex; } ;
struct i915_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kernel_context; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i915_request*) ; 
 int PTR_ERR (struct i915_request*) ; 
 int gen8_emit_rpcs_config (struct i915_request*,struct intel_context*,struct intel_sseu) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 
 struct i915_request* i915_request_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_context_is_pinned (struct intel_context*) ; 
 int intel_context_prepare_remote_request (struct intel_context*,struct i915_request*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gen8_modify_rpcs(struct intel_context *ce, struct intel_sseu sseu)
{
	struct i915_request *rq;
	int ret;

	lockdep_assert_held(&ce->pin_mutex);

	/*
	 * If the context is not idle, we have to submit an ordered request to
	 * modify its context image via the kernel context (writing to our own
	 * image, or into the registers directory, does not stick). Pristine
	 * and idle contexts will be configured on pinning.
	 */
	if (!intel_context_is_pinned(ce))
		return 0;

	rq = i915_request_create(ce->engine->kernel_context);
	if (IS_ERR(rq))
		return PTR_ERR(rq);

	/* Serialise with the remote context */
	ret = intel_context_prepare_remote_request(ce, rq);
	if (ret == 0)
		ret = gen8_emit_rpcs_config(rq, ce, sseu);

	i915_request_add(rq);
	return ret;
}