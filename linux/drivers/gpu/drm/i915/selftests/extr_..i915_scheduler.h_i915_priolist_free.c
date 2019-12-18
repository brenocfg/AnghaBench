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
struct i915_priolist {scalar_t__ priority; } ;

/* Variables and functions */
 scalar_t__ I915_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  __i915_priolist_free (struct i915_priolist*) ; 

__attribute__((used)) static inline void i915_priolist_free(struct i915_priolist *p)
{
	if (p->priority != I915_PRIORITY_NORMAL)
		__i915_priolist_free(p);
}