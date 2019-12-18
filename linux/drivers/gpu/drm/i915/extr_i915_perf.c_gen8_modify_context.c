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
struct intel_context {TYPE_1__* engine; int /*<<< orphan*/  pin_mutex; } ;
struct i915_request {int dummy; } ;
struct flex {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kernel_context; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i915_request*) ; 
 int PTR_ERR (struct i915_request*) ; 
 int gen8_store_flex (struct i915_request*,struct intel_context*,struct flex const*,unsigned int) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 
 struct i915_request* i915_request_create (int /*<<< orphan*/ ) ; 
 int intel_context_prepare_remote_request (struct intel_context*,struct i915_request*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gen8_modify_context(struct intel_context *ce,
			       const struct flex *flex, unsigned int count)
{
	struct i915_request *rq;
	int err;

	lockdep_assert_held(&ce->pin_mutex);

	rq = i915_request_create(ce->engine->kernel_context);
	if (IS_ERR(rq))
		return PTR_ERR(rq);

	/* Serialise with the remote context */
	err = intel_context_prepare_remote_request(ce, rq);
	if (err == 0)
		err = gen8_store_flex(rq, ce, flex, count);

	i915_request_add(rq);
	return err;
}