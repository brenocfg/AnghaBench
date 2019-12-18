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
struct i915_ppgtt {int /*<<< orphan*/  vm; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i915_ppgtt*) ; 
 struct i915_ppgtt* __ppgtt_create (struct drm_i915_private*) ; 
 int /*<<< orphan*/  trace_i915_ppgtt_create (int /*<<< orphan*/ *) ; 

struct i915_ppgtt *
i915_ppgtt_create(struct drm_i915_private *i915)
{
	struct i915_ppgtt *ppgtt;

	ppgtt = __ppgtt_create(i915);
	if (IS_ERR(ppgtt))
		return ppgtt;

	trace_i915_ppgtt_create(&ppgtt->vm);

	return ppgtt;
}