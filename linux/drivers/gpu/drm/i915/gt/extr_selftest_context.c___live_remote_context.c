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
struct intel_engine_cs {int /*<<< orphan*/  name; struct intel_context* kernel_context; } ;
struct intel_context {int /*<<< orphan*/  active; } ;
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct intel_context*) ; 
 int PTR_ERR (struct intel_context*) ; 
 int __remote_sync (struct intel_context*,struct intel_context*) ; 
 scalar_t__ i915_active_is_idle (int /*<<< orphan*/ *) ; 
 struct intel_context* intel_context_create (struct i915_gem_context*,struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_context_put (struct intel_context*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __live_remote_context(struct intel_engine_cs *engine,
				 struct i915_gem_context *fixme)
{
	struct intel_context *local, *remote;
	int pass;
	int err;

	/*
	 * Check that our idle barriers do not interfere with normal
	 * activity tracking. In particular, check that operating
	 * on the context image remotely (intel_context_prepare_remote_request),
	 * which inserts foreign fences into intel_context.active, does not
	 * clobber the idle-barrier.
	 */

	remote = intel_context_create(fixme, engine);
	if (IS_ERR(remote))
		return PTR_ERR(remote);

	local = intel_context_create(fixme, engine);
	if (IS_ERR(local)) {
		err = PTR_ERR(local);
		goto err_remote;
	}

	for (pass = 0; pass <= 2; pass++) {
		err = __remote_sync(local, remote);
		if (err)
			break;

		err = __remote_sync(engine->kernel_context, remote);
		if (err)
			break;

		if (i915_active_is_idle(&remote->active)) {
			pr_err("remote context is not active; expected idle-barrier (%s pass %d)\n",
			       engine->name, pass);
			err = -EINVAL;
			break;
		}
	}

	intel_context_put(local);
err_remote:
	intel_context_put(remote);
	return err;
}