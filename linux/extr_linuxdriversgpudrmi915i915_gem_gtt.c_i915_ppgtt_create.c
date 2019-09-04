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
struct TYPE_2__ {struct drm_i915_file_private* file; } ;
struct i915_hw_ppgtt {TYPE_1__ vm; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_file_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i915_hw_ppgtt*) ; 
 struct i915_hw_ppgtt* __hw_ppgtt_create (struct drm_i915_private*) ; 
 int /*<<< orphan*/  trace_i915_ppgtt_create (TYPE_1__*) ; 

struct i915_hw_ppgtt *
i915_ppgtt_create(struct drm_i915_private *i915,
		  struct drm_i915_file_private *fpriv)
{
	struct i915_hw_ppgtt *ppgtt;

	ppgtt = __hw_ppgtt_create(i915);
	if (IS_ERR(ppgtt))
		return ppgtt;

	ppgtt->vm.file = fpriv;

	trace_i915_ppgtt_create(&ppgtt->vm);

	return ppgtt;
}