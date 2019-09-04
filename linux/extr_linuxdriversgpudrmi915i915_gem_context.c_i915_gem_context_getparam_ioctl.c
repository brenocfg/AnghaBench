#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int priority; } ;
struct i915_gem_context {int flags; TYPE_8__ sched; TYPE_2__* ppgtt; } ;
struct drm_i915_gem_context_param {int param; int value; scalar_t__ size; int /*<<< orphan*/  ctx_id; } ;
struct drm_i915_file_private {int dummy; } ;
struct drm_file {struct drm_i915_file_private* driver_priv; } ;
struct drm_device {int dummy; } ;
struct TYPE_15__ {int total; } ;
struct TYPE_16__ {TYPE_6__ vm; } ;
struct TYPE_14__ {TYPE_4__* aliasing_ppgtt; } ;
struct TYPE_18__ {TYPE_7__ ggtt; TYPE_5__ mm; } ;
struct TYPE_12__ {int total; } ;
struct TYPE_13__ {TYPE_3__ vm; } ;
struct TYPE_10__ {int total; } ;
struct TYPE_11__ {TYPE_1__ vm; } ;

/* Variables and functions */
 int CONTEXT_NO_ZEROMAP ; 
 int EINVAL ; 
 int ENOENT ; 
#define  I915_CONTEXT_PARAM_BANNABLE 133 
#define  I915_CONTEXT_PARAM_BAN_PERIOD 132 
#define  I915_CONTEXT_PARAM_GTT_SIZE 131 
#define  I915_CONTEXT_PARAM_NO_ERROR_CAPTURE 130 
#define  I915_CONTEXT_PARAM_NO_ZEROMAP 129 
#define  I915_CONTEXT_PARAM_PRIORITY 128 
 int i915_gem_context_is_bannable (struct i915_gem_context*) ; 
 struct i915_gem_context* i915_gem_context_lookup (struct drm_i915_file_private*,int /*<<< orphan*/ ) ; 
 int i915_gem_context_no_error_capture (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_put (struct i915_gem_context*) ; 
 TYPE_9__* to_i915 (struct drm_device*) ; 

int i915_gem_context_getparam_ioctl(struct drm_device *dev, void *data,
				    struct drm_file *file)
{
	struct drm_i915_file_private *file_priv = file->driver_priv;
	struct drm_i915_gem_context_param *args = data;
	struct i915_gem_context *ctx;
	int ret = 0;

	ctx = i915_gem_context_lookup(file_priv, args->ctx_id);
	if (!ctx)
		return -ENOENT;

	args->size = 0;
	switch (args->param) {
	case I915_CONTEXT_PARAM_BAN_PERIOD:
		ret = -EINVAL;
		break;
	case I915_CONTEXT_PARAM_NO_ZEROMAP:
		args->value = ctx->flags & CONTEXT_NO_ZEROMAP;
		break;
	case I915_CONTEXT_PARAM_GTT_SIZE:
		if (ctx->ppgtt)
			args->value = ctx->ppgtt->vm.total;
		else if (to_i915(dev)->mm.aliasing_ppgtt)
			args->value = to_i915(dev)->mm.aliasing_ppgtt->vm.total;
		else
			args->value = to_i915(dev)->ggtt.vm.total;
		break;
	case I915_CONTEXT_PARAM_NO_ERROR_CAPTURE:
		args->value = i915_gem_context_no_error_capture(ctx);
		break;
	case I915_CONTEXT_PARAM_BANNABLE:
		args->value = i915_gem_context_is_bannable(ctx);
		break;
	case I915_CONTEXT_PARAM_PRIORITY:
		args->value = ctx->sched.priority;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	i915_gem_context_put(ctx);
	return ret;
}