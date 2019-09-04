#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct intel_context {struct i915_gem_context* gem_context; } ;
struct TYPE_8__ {int /*<<< orphan*/  priority; } ;
struct i915_gem_context {int user_handle; int ring_size; int /*<<< orphan*/  pid; int /*<<< orphan*/  ggtt_offset_bias; int /*<<< orphan*/  desc_template; int /*<<< orphan*/  remap_slice; int /*<<< orphan*/  name; struct drm_i915_file_private* file_priv; int /*<<< orphan*/  handles_list; int /*<<< orphan*/  handles_vma; struct intel_context* __engine; TYPE_2__ sched; struct drm_i915_private* i915; int /*<<< orphan*/  link; int /*<<< orphan*/  ref; int /*<<< orphan*/  hw_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  ggtt_pin_bias; } ;
struct TYPE_9__ {int /*<<< orphan*/  aliasing_ppgtt; } ;
struct TYPE_7__ {int /*<<< orphan*/  list; } ;
struct drm_i915_private {TYPE_4__ guc; TYPE_3__ mm; TYPE_1__ contexts; } ;
struct drm_i915_file_private {int /*<<< orphan*/  context_idr; } ;
struct TYPE_11__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_L3_SLICES (struct drm_i915_private*) ; 
 unsigned int ARRAY_SIZE (struct intel_context*) ; 
 int DEFAULT_CONTEXT_HANDLE ; 
 int ENOMEM ; 
 struct i915_gem_context* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE ; 
 int /*<<< orphan*/  I915_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 scalar_t__ USES_GUC (struct drm_i915_private*) ; 
 int assign_hw_id (struct drm_i915_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  context_close (struct i915_gem_context*) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  default_desc_template (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_pid (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_set_bannable (struct i915_gem_context*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct i915_gem_context*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct i915_gem_context*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct i915_gem_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct i915_gem_context *
__create_hw_context(struct drm_i915_private *dev_priv,
		    struct drm_i915_file_private *file_priv)
{
	struct i915_gem_context *ctx;
	unsigned int n;
	int ret;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (ctx == NULL)
		return ERR_PTR(-ENOMEM);

	ret = assign_hw_id(dev_priv, &ctx->hw_id);
	if (ret) {
		kfree(ctx);
		return ERR_PTR(ret);
	}

	kref_init(&ctx->ref);
	list_add_tail(&ctx->link, &dev_priv->contexts.list);
	ctx->i915 = dev_priv;
	ctx->sched.priority = I915_PRIORITY_NORMAL;

	for (n = 0; n < ARRAY_SIZE(ctx->__engine); n++) {
		struct intel_context *ce = &ctx->__engine[n];

		ce->gem_context = ctx;
	}

	INIT_RADIX_TREE(&ctx->handles_vma, GFP_KERNEL);
	INIT_LIST_HEAD(&ctx->handles_list);

	/* Default context will never have a file_priv */
	ret = DEFAULT_CONTEXT_HANDLE;
	if (file_priv) {
		ret = idr_alloc(&file_priv->context_idr, ctx,
				DEFAULT_CONTEXT_HANDLE, 0, GFP_KERNEL);
		if (ret < 0)
			goto err_lut;
	}
	ctx->user_handle = ret;

	ctx->file_priv = file_priv;
	if (file_priv) {
		ctx->pid = get_task_pid(current, PIDTYPE_PID);
		ctx->name = kasprintf(GFP_KERNEL, "%s[%d]/%x",
				      current->comm,
				      pid_nr(ctx->pid),
				      ctx->user_handle);
		if (!ctx->name) {
			ret = -ENOMEM;
			goto err_pid;
		}
	}

	/* NB: Mark all slices as needing a remap so that when the context first
	 * loads it will restore whatever remap state already exists. If there
	 * is no remap info, it will be a NOP. */
	ctx->remap_slice = ALL_L3_SLICES(dev_priv);

	i915_gem_context_set_bannable(ctx);
	ctx->ring_size = 4 * PAGE_SIZE;
	ctx->desc_template =
		default_desc_template(dev_priv, dev_priv->mm.aliasing_ppgtt);

	/*
	 * GuC requires the ring to be placed in Non-WOPCM memory. If GuC is not
	 * present or not in use we still need a small bias as ring wraparound
	 * at offset 0 sometimes hangs. No idea why.
	 */
	if (USES_GUC(dev_priv))
		ctx->ggtt_offset_bias = dev_priv->guc.ggtt_pin_bias;
	else
		ctx->ggtt_offset_bias = I915_GTT_PAGE_SIZE;

	return ctx;

err_pid:
	put_pid(ctx->pid);
	idr_remove(&file_priv->context_idr, ctx->user_handle);
err_lut:
	context_close(ctx);
	return ERR_PTR(ret);
}