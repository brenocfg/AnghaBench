#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i915_gem_context {int /*<<< orphan*/  user_handle; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_context_create {scalar_t__ pad; int /*<<< orphan*/  ctx_id; } ;
struct drm_i915_file_private {int dummy; } ;
struct drm_file {struct drm_i915_file_private* driver_priv; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  has_logical_contexts; } ;
struct TYPE_4__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 TYPE_3__* DRIVER_CAPS (struct drm_i915_private*) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,...) ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct i915_gem_context*) ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int PTR_ERR (struct i915_gem_context*) ; 
 scalar_t__ client_is_banned (struct drm_i915_file_private*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  get_task_pid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_is_kernel (struct i915_gem_context*) ; 
 struct i915_gem_context* i915_gem_create_context (struct drm_i915_private*,struct drm_i915_file_private*) ; 
 int i915_mutex_lock_interruptible (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pid_nr (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

int i915_gem_context_create_ioctl(struct drm_device *dev, void *data,
				  struct drm_file *file)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_i915_gem_context_create *args = data;
	struct drm_i915_file_private *file_priv = file->driver_priv;
	struct i915_gem_context *ctx;
	int ret;

	if (!DRIVER_CAPS(dev_priv)->has_logical_contexts)
		return -ENODEV;

	if (args->pad != 0)
		return -EINVAL;

	if (client_is_banned(file_priv)) {
		DRM_DEBUG("client %s[%d] banned from creating ctx\n",
			  current->comm,
			  pid_nr(get_task_pid(current, PIDTYPE_PID)));

		return -EIO;
	}

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	ctx = i915_gem_create_context(dev_priv, file_priv);
	mutex_unlock(&dev->struct_mutex);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	GEM_BUG_ON(i915_gem_context_is_kernel(ctx));

	args->ctx_id = ctx->user_handle;
	DRM_DEBUG("HW context %d created\n", args->ctx_id);

	return 0;
}