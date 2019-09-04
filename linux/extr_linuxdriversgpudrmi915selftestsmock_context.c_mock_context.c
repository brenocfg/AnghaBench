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
struct intel_context {struct i915_gem_context* gem_context; } ;
struct i915_gem_context {int hw_id; int /*<<< orphan*/  ppgtt; int /*<<< orphan*/  name; struct intel_context* __engine; int /*<<< orphan*/  handles_list; int /*<<< orphan*/  handles_vma; struct drm_i915_private* i915; int /*<<< orphan*/  link; int /*<<< orphan*/  ref; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_ida; } ;
struct drm_i915_private {TYPE_1__ contexts; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct intel_context*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_CONTEXT_HW_ID ; 
 int /*<<< orphan*/  i915_gem_context_put (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_closed (struct i915_gem_context*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i915_gem_context*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct i915_gem_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mock_ppgtt (struct drm_i915_private*,char const*) ; 

struct i915_gem_context *
mock_context(struct drm_i915_private *i915,
	     const char *name)
{
	struct i915_gem_context *ctx;
	unsigned int n;
	int ret;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return NULL;

	kref_init(&ctx->ref);
	INIT_LIST_HEAD(&ctx->link);
	ctx->i915 = i915;

	INIT_RADIX_TREE(&ctx->handles_vma, GFP_KERNEL);
	INIT_LIST_HEAD(&ctx->handles_list);

	for (n = 0; n < ARRAY_SIZE(ctx->__engine); n++) {
		struct intel_context *ce = &ctx->__engine[n];

		ce->gem_context = ctx;
	}

	ret = ida_simple_get(&i915->contexts.hw_ida,
			     0, MAX_CONTEXT_HW_ID, GFP_KERNEL);
	if (ret < 0)
		goto err_handles;
	ctx->hw_id = ret;

	if (name) {
		ctx->name = kstrdup(name, GFP_KERNEL);
		if (!ctx->name)
			goto err_put;

		ctx->ppgtt = mock_ppgtt(i915, name);
		if (!ctx->ppgtt)
			goto err_put;
	}

	return ctx;

err_handles:
	kfree(ctx);
	return NULL;

err_put:
	i915_gem_context_set_closed(ctx);
	i915_gem_context_put(ctx);
	return NULL;
}