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
struct i915_syncmap {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 struct i915_syncmap** __sync_child (struct i915_syncmap*) ; 

__attribute__((used)) static inline void __sync_set_child(struct i915_syncmap *p,
				    unsigned int idx,
				    struct i915_syncmap *child)
{
	p->bitmap |= BIT(idx);
	__sync_child(p)[idx] = child;
}