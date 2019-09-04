#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  priority; } ;
struct i915_gem_context {TYPE_2__ sched; int /*<<< orphan*/  flags; } ;
struct drm_i915_gem_context_param {int param; int /*<<< orphan*/  size; int /*<<< orphan*/  value; int /*<<< orphan*/  ctx_id; } ;
struct drm_i915_file_private {int dummy; } ;
struct drm_file {struct drm_i915_file_private* driver_priv; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_4__ {int scheduler; } ;
struct TYPE_6__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CAP_SYS_NICE ; 
 int /*<<< orphan*/  CONTEXT_NO_ZEROMAP ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  I915_CONTEXT_DEFAULT_PRIORITY ; 
 int /*<<< orphan*/  I915_CONTEXT_MAX_USER_PRIORITY ; 
 int /*<<< orphan*/  I915_CONTEXT_MIN_USER_PRIORITY ; 
#define  I915_CONTEXT_PARAM_BANNABLE 132 
#define  I915_CONTEXT_PARAM_BAN_PERIOD 131 
#define  I915_CONTEXT_PARAM_NO_ERROR_CAPTURE 130 
#define  I915_CONTEXT_PARAM_NO_ZEROMAP 129 
#define  I915_CONTEXT_PARAM_PRIORITY 128 
 int I915_SCHEDULER_CAP_PRIORITY ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_clear_bannable (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_clear_no_error_capture (struct i915_gem_context*) ; 
 struct i915_gem_context* i915_gem_context_lookup (struct drm_i915_file_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_put (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_bannable (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_no_error_capture (struct i915_gem_context*) ; 
 int i915_mutex_lock_interruptible (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* to_i915 (struct drm_device*) ; 

int i915_gem_context_setparam_ioctl(struct drm_device *dev, void *data,
				    struct drm_file *file)
{
	struct drm_i915_file_private *file_priv = file->driver_priv;
	struct drm_i915_gem_context_param *args = data;
	struct i915_gem_context *ctx;
	int ret;

	ctx = i915_gem_context_lookup(file_priv, args->ctx_id);
	if (!ctx)
		return -ENOENT;

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		goto out;

	switch (args->param) {
	case I915_CONTEXT_PARAM_BAN_PERIOD:
		ret = -EINVAL;
		break;
	case I915_CONTEXT_PARAM_NO_ZEROMAP:
		if (args->size) {
			ret = -EINVAL;
		} else {
			ctx->flags &= ~CONTEXT_NO_ZEROMAP;
			ctx->flags |= args->value ? CONTEXT_NO_ZEROMAP : 0;
		}
		break;
	case I915_CONTEXT_PARAM_NO_ERROR_CAPTURE:
		if (args->size)
			ret = -EINVAL;
		else if (args->value)
			i915_gem_context_set_no_error_capture(ctx);
		else
			i915_gem_context_clear_no_error_capture(ctx);
		break;
	case I915_CONTEXT_PARAM_BANNABLE:
		if (args->size)
			ret = -EINVAL;
		else if (!capable(CAP_SYS_ADMIN) && !args->value)
			ret = -EPERM;
		else if (args->value)
			i915_gem_context_set_bannable(ctx);
		else
			i915_gem_context_clear_bannable(ctx);
		break;

	case I915_CONTEXT_PARAM_PRIORITY:
		{
			s64 priority = args->value;

			if (args->size)
				ret = -EINVAL;
			else if (!(to_i915(dev)->caps.scheduler & I915_SCHEDULER_CAP_PRIORITY))
				ret = -ENODEV;
			else if (priority > I915_CONTEXT_MAX_USER_PRIORITY ||
				 priority < I915_CONTEXT_MIN_USER_PRIORITY)
				ret = -EINVAL;
			else if (priority > I915_CONTEXT_DEFAULT_PRIORITY &&
				 !capable(CAP_SYS_NICE))
				ret = -EPERM;
			else
				ctx->sched.priority = priority;
		}
		break;

	default:
		ret = -EINVAL;
		break;
	}
	mutex_unlock(&dev->struct_mutex);

out:
	i915_gem_context_put(ctx);
	return ret;
}