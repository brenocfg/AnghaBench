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
struct i915_gpu_state {char const* error_msg; TYPE_2__* engine; int /*<<< orphan*/  i915; } ;
typedef  int /*<<< orphan*/  intel_engine_mask_t ;
struct TYPE_3__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;
struct TYPE_4__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_error_generate_code (struct i915_gpu_state*) ; 
 int scnprintf (char const*,int,char*,char const*,...) ; 

__attribute__((used)) static const char *
error_msg(struct i915_gpu_state *error,
	  intel_engine_mask_t engines, const char *msg)
{
	int len;

	len = scnprintf(error->error_msg, sizeof(error->error_msg),
			"GPU HANG: ecode %d:%x:0x%08x",
			INTEL_GEN(error->i915), engines,
			i915_error_generate_code(error));
	if (error->engine) {
		/* Just show the first executing process, more is confusing */
		len += scnprintf(error->error_msg + len,
				 sizeof(error->error_msg) - len,
				 ", in %s [%d]",
				 error->engine->context.comm,
				 error->engine->context.pid);
	}
	if (msg)
		len += scnprintf(error->error_msg + len,
				 sizeof(error->error_msg) - len,
				 ", %s", msg);

	return error->error_msg;
}