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
struct i915_hw_ppgtt {int dummy; } ;
struct i915_gem_context {TYPE_2__* i915; int /*<<< orphan*/  ppgtt; } ;
struct TYPE_3__ {struct i915_hw_ppgtt* aliasing_ppgtt; } ;
struct TYPE_4__ {TYPE_1__ mm; } ;

/* Variables and functions */
 int gen6_ppgtt_pin (struct i915_hw_ppgtt*) ; 

__attribute__((used)) static int __context_pin_ppgtt(struct i915_gem_context *ctx)
{
	struct i915_hw_ppgtt *ppgtt;
	int err = 0;

	ppgtt = ctx->ppgtt ?: ctx->i915->mm.aliasing_ppgtt;
	if (ppgtt)
		err = gen6_ppgtt_pin(ppgtt);

	return err;
}