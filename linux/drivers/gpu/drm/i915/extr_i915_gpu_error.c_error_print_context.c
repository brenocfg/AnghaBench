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
struct drm_i915_error_state_buf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  priority; } ;
struct drm_i915_error_context {int /*<<< orphan*/  active; int /*<<< orphan*/  guilty; TYPE_1__ sched_attr; int /*<<< orphan*/  hw_id; int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  err_printf (struct drm_i915_error_state_buf*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void error_print_context(struct drm_i915_error_state_buf *m,
				const char *header,
				const struct drm_i915_error_context *ctx)
{
	err_printf(m, "%s%s[%d] hw_id %d, prio %d, guilty %d active %d\n",
		   header, ctx->comm, ctx->pid, ctx->hw_id,
		   ctx->sched_attr.priority, ctx->guilty, ctx->active);
}