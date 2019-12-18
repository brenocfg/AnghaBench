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
struct i915_buddy_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ I915_BUDDY_SPLIT ; 
 scalar_t__ i915_buddy_block_state (struct i915_buddy_block*) ; 

__attribute__((used)) static inline bool
i915_buddy_block_is_split(struct i915_buddy_block *block)
{
	return i915_buddy_block_state(block) == I915_BUDDY_SPLIT;
}