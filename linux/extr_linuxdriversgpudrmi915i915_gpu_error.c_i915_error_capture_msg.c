#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct i915_gpu_state {int /*<<< orphan*/  error_msg; TYPE_2__* engine; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {char* pid; char const* comm; } ;
struct TYPE_4__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ i915_error_generate_code (struct drm_i915_private*,struct i915_gpu_state*,int*) ; 
 int scnprintf (int /*<<< orphan*/ ,int,char*,char const*,...) ; 

__attribute__((used)) static void i915_error_capture_msg(struct drm_i915_private *dev_priv,
				   struct i915_gpu_state *error,
				   u32 engine_mask,
				   const char *error_msg)
{
	u32 ecode;
	int engine_id = -1, len;

	ecode = i915_error_generate_code(dev_priv, error, &engine_id);

	len = scnprintf(error->error_msg, sizeof(error->error_msg),
			"GPU HANG: ecode %d:%d:0x%08x",
			INTEL_GEN(dev_priv), engine_id, ecode);

	if (engine_id != -1 && error->engine[engine_id].context.pid)
		len += scnprintf(error->error_msg + len,
				 sizeof(error->error_msg) - len,
				 ", in %s [%d]",
				 error->engine[engine_id].context.comm,
				 error->engine[engine_id].context.pid);

	scnprintf(error->error_msg + len, sizeof(error->error_msg) - len,
		  ", reason: %s, action: %s",
		  error_msg,
		  engine_mask ? "reset" : "continue");
}