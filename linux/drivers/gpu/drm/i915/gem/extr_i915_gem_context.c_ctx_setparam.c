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
struct TYPE_6__ {int /*<<< orphan*/  priority; } ;
struct i915_gem_context {TYPE_3__ sched; TYPE_2__* i915; int /*<<< orphan*/  user_flags; } ;
struct drm_i915_gem_context_param {int param; int /*<<< orphan*/  size; int /*<<< orphan*/  value; } ;
struct drm_i915_file_private {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_4__ {int scheduler; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CAP_SYS_NICE ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  I915_CONTEXT_DEFAULT_PRIORITY ; 
 int /*<<< orphan*/  I915_CONTEXT_MAX_USER_PRIORITY ; 
 int /*<<< orphan*/  I915_CONTEXT_MIN_USER_PRIORITY ; 
#define  I915_CONTEXT_PARAM_BANNABLE 136 
#define  I915_CONTEXT_PARAM_BAN_PERIOD 135 
#define  I915_CONTEXT_PARAM_ENGINES 134 
#define  I915_CONTEXT_PARAM_NO_ERROR_CAPTURE 133 
#define  I915_CONTEXT_PARAM_NO_ZEROMAP 132 
#define  I915_CONTEXT_PARAM_PRIORITY 131 
#define  I915_CONTEXT_PARAM_RECOVERABLE 130 
#define  I915_CONTEXT_PARAM_SSEU 129 
#define  I915_CONTEXT_PARAM_VM 128 
 int I915_SCHEDULER_CAP_PRIORITY ; 
 int /*<<< orphan*/  I915_USER_PRIORITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UCONTEXT_NO_ZEROMAP ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_context_clear_bannable (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_clear_no_error_capture (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_clear_recoverable (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_bannable (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_no_error_capture (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_recoverable (struct i915_gem_context*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int set_engines (struct i915_gem_context*,struct drm_i915_gem_context_param*) ; 
 int set_ppgtt (struct drm_i915_file_private*,struct i915_gem_context*,struct drm_i915_gem_context_param*) ; 
 int set_sseu (struct i915_gem_context*,struct drm_i915_gem_context_param*) ; 

__attribute__((used)) static int ctx_setparam(struct drm_i915_file_private *fpriv,
			struct i915_gem_context *ctx,
			struct drm_i915_gem_context_param *args)
{
	int ret = 0;

	switch (args->param) {
	case I915_CONTEXT_PARAM_NO_ZEROMAP:
		if (args->size)
			ret = -EINVAL;
		else if (args->value)
			set_bit(UCONTEXT_NO_ZEROMAP, &ctx->user_flags);
		else
			clear_bit(UCONTEXT_NO_ZEROMAP, &ctx->user_flags);
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

	case I915_CONTEXT_PARAM_RECOVERABLE:
		if (args->size)
			ret = -EINVAL;
		else if (args->value)
			i915_gem_context_set_recoverable(ctx);
		else
			i915_gem_context_clear_recoverable(ctx);
		break;

	case I915_CONTEXT_PARAM_PRIORITY:
		{
			s64 priority = args->value;

			if (args->size)
				ret = -EINVAL;
			else if (!(ctx->i915->caps.scheduler & I915_SCHEDULER_CAP_PRIORITY))
				ret = -ENODEV;
			else if (priority > I915_CONTEXT_MAX_USER_PRIORITY ||
				 priority < I915_CONTEXT_MIN_USER_PRIORITY)
				ret = -EINVAL;
			else if (priority > I915_CONTEXT_DEFAULT_PRIORITY &&
				 !capable(CAP_SYS_NICE))
				ret = -EPERM;
			else
				ctx->sched.priority =
					I915_USER_PRIORITY(priority);
		}
		break;

	case I915_CONTEXT_PARAM_SSEU:
		ret = set_sseu(ctx, args);
		break;

	case I915_CONTEXT_PARAM_VM:
		ret = set_ppgtt(fpriv, ctx, args);
		break;

	case I915_CONTEXT_PARAM_ENGINES:
		ret = set_engines(ctx, args);
		break;

	case I915_CONTEXT_PARAM_BAN_PERIOD:
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}