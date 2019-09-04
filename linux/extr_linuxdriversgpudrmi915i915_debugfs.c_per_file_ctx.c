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
struct seq_file {int dummy; } ;
struct i915_hw_ppgtt {int /*<<< orphan*/  (* debug_dump ) (struct i915_hw_ppgtt*,struct seq_file*) ;} ;
struct i915_gem_context {int /*<<< orphan*/  user_handle; struct i915_hw_ppgtt* ppgtt; } ;

/* Variables and functions */
 scalar_t__ i915_gem_context_is_default (struct i915_gem_context*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  stub1 (struct i915_hw_ppgtt*,struct seq_file*) ; 

__attribute__((used)) static int per_file_ctx(int id, void *ptr, void *data)
{
	struct i915_gem_context *ctx = ptr;
	struct seq_file *m = data;
	struct i915_hw_ppgtt *ppgtt = ctx->ppgtt;

	if (!ppgtt) {
		seq_printf(m, "  no ppgtt for context %d\n",
			   ctx->user_handle);
		return 0;
	}

	if (i915_gem_context_is_default(ctx))
		seq_puts(m, "  default context:\n");
	else
		seq_printf(m, "  context %d:\n", ctx->user_handle);
	ppgtt->debug_dump(ppgtt, m);

	return 0;
}