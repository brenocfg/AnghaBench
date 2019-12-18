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
struct intel_context {int dummy; } ;
struct i915_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i915_request*) ; 
 int PTR_ERR (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 
 struct i915_request* intel_context_create_request (struct intel_context*) ; 
 int intel_context_pin (struct intel_context*) ; 
 int intel_context_prepare_remote_request (struct intel_context*,struct i915_request*) ; 
 int /*<<< orphan*/  intel_context_unpin (struct intel_context*) ; 
 int request_sync (struct i915_request*) ; 

__attribute__((used)) static int __remote_sync(struct intel_context *ce, struct intel_context *remote)
{
	struct i915_request *rq;
	int err;

	err = intel_context_pin(remote);
	if (err)
		return err;

	rq = intel_context_create_request(ce);
	if (IS_ERR(rq)) {
		err = PTR_ERR(rq);
		goto unpin;
	}

	err = intel_context_prepare_remote_request(remote, rq);
	if (err) {
		i915_request_add(rq);
		goto unpin;
	}

	err = request_sync(rq);

unpin:
	intel_context_unpin(remote);
	return err;
}