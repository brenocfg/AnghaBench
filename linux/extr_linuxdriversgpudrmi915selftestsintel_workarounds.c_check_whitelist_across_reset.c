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
struct whitelist {int dummy; } ;
struct intel_engine_cs {int /*<<< orphan*/  i915; } ;
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i915_gem_context*) ; 
 int PTR_ERR (struct i915_gem_context*) ; 
 int check_whitelist (struct whitelist const*,struct i915_gem_context*,struct intel_engine_cs*) ; 
 struct i915_gem_context* kernel_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_context_close (struct i915_gem_context*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int switch_to_scratch_context (struct intel_engine_cs*) ; 

__attribute__((used)) static int check_whitelist_across_reset(struct intel_engine_cs *engine,
					int (*reset)(struct intel_engine_cs *),
					const struct whitelist *w,
					const char *name)
{
	struct i915_gem_context *ctx;
	int err;

	ctx = kernel_context(engine->i915);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	err = check_whitelist(w, ctx, engine);
	if (err) {
		pr_err("Invalid whitelist *before* %s reset!\n", name);
		goto out;
	}

	err = switch_to_scratch_context(engine);
	if (err)
		goto out;

	err = reset(engine);
	if (err) {
		pr_err("%s reset failed\n", name);
		goto out;
	}

	err = check_whitelist(w, ctx, engine);
	if (err) {
		pr_err("Whitelist not preserved in context across %s reset!\n",
		       name);
		goto out;
	}

	kernel_context_close(ctx);

	ctx = kernel_context(engine->i915);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	err = check_whitelist(w, ctx, engine);
	if (err) {
		pr_err("Invalid whitelist *after* %s reset in fresh context!\n",
		       name);
		goto out;
	}

out:
	kernel_context_close(ctx);
	return err;
}