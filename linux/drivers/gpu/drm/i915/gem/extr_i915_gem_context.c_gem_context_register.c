#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i915_gem_context {int /*<<< orphan*/  pid; int /*<<< orphan*/  name; TYPE_1__* vm; struct drm_i915_file_private* file_priv; } ;
struct drm_i915_file_private {int /*<<< orphan*/  context_idr_lock; int /*<<< orphan*/  context_idr; } ;
struct TYPE_5__ {int /*<<< orphan*/  comm; } ;
struct TYPE_4__ {struct drm_i915_file_private* file; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_task_pid (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct i915_gem_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gem_context_register(struct i915_gem_context *ctx,
				struct drm_i915_file_private *fpriv)
{
	int ret;

	ctx->file_priv = fpriv;
	if (ctx->vm)
		ctx->vm->file = fpriv;

	ctx->pid = get_task_pid(current, PIDTYPE_PID);
	ctx->name = kasprintf(GFP_KERNEL, "%s[%d]",
			      current->comm, pid_nr(ctx->pid));
	if (!ctx->name) {
		ret = -ENOMEM;
		goto err_pid;
	}

	/* And finally expose ourselves to userspace via the idr */
	mutex_lock(&fpriv->context_idr_lock);
	ret = idr_alloc(&fpriv->context_idr, ctx, 0, 0, GFP_KERNEL);
	mutex_unlock(&fpriv->context_idr_lock);
	if (ret >= 0)
		goto out;

	kfree(fetch_and_zero(&ctx->name));
err_pid:
	put_pid(fetch_and_zero(&ctx->pid));
out:
	return ret;
}