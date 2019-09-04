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
struct i915_vma {int active_count; } ;

/* Variables and functions */

__attribute__((used)) static inline bool i915_vma_is_active(struct i915_vma *vma)
{
	return vma->active_count;
}