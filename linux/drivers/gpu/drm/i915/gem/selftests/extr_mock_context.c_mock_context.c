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
struct i915_ppgtt {int /*<<< orphan*/  vm; } ;
struct i915_gem_engines {int dummy; } ;
struct i915_gem_context {int /*<<< orphan*/  engines; int /*<<< orphan*/  name; int /*<<< orphan*/  mutex; int /*<<< orphan*/  hw_id_link; int /*<<< orphan*/  handles_vma; int /*<<< orphan*/  engines_mutex; struct drm_i915_private* i915; int /*<<< orphan*/  link; int /*<<< orphan*/  ref; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct i915_gem_engines*) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct i915_gem_engines*) ; 
 int /*<<< orphan*/  __set_ppgtt (struct i915_gem_context*,int /*<<< orphan*/ *) ; 
 struct i915_gem_engines* default_engines (struct i915_gem_context*) ; 
 int /*<<< orphan*/  free_engines (int /*<<< orphan*/ ) ; 
 int i915_gem_context_pin_hw_id (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_put (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_closed (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_vm_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct i915_gem_context*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct i915_gem_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct i915_ppgtt* mock_ppgtt (struct drm_i915_private*,char const*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 

struct i915_gem_context *
mock_context(struct drm_i915_private *i915,
	     const char *name)
{
	struct i915_gem_context *ctx;
	struct i915_gem_engines *e;
	int ret;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return NULL;

	kref_init(&ctx->ref);
	INIT_LIST_HEAD(&ctx->link);
	ctx->i915 = i915;

	mutex_init(&ctx->engines_mutex);
	e = default_engines(ctx);
	if (IS_ERR(e))
		goto err_free;
	RCU_INIT_POINTER(ctx->engines, e);

	INIT_RADIX_TREE(&ctx->handles_vma, GFP_KERNEL);
	INIT_LIST_HEAD(&ctx->hw_id_link);
	mutex_init(&ctx->mutex);

	ret = i915_gem_context_pin_hw_id(ctx);
	if (ret < 0)
		goto err_engines;

	if (name) {
		struct i915_ppgtt *ppgtt;

		ctx->name = kstrdup(name, GFP_KERNEL);
		if (!ctx->name)
			goto err_put;

		ppgtt = mock_ppgtt(i915, name);
		if (!ppgtt)
			goto err_put;

		__set_ppgtt(ctx, &ppgtt->vm);
		i915_vm_put(&ppgtt->vm);
	}

	return ctx;

err_engines:
	free_engines(rcu_access_pointer(ctx->engines));
err_free:
	kfree(ctx);
	return NULL;

err_put:
	i915_gem_context_set_closed(ctx);
	i915_gem_context_put(ctx);
	return NULL;
}