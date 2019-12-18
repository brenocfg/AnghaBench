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
typedef  int /*<<< orphan*/  u32 ;
struct i915_vma {int /*<<< orphan*/  vm; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin_bias; } ;

/* Variables and functions */
 TYPE_1__* i915_vm_to_ggtt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 i915_ggtt_pin_bias(struct i915_vma *vma)
{
	return i915_vm_to_ggtt(vma->vm)->pin_bias;
}