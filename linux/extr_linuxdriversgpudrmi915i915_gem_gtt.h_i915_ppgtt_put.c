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
struct i915_hw_ppgtt {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_ppgtt_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void i915_ppgtt_put(struct i915_hw_ppgtt *ppgtt)
{
	if (ppgtt)
		kref_put(&ppgtt->ref, i915_ppgtt_release);
}