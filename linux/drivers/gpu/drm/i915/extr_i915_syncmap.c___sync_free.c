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
struct i915_syncmap {unsigned int bitmap; scalar_t__ height; } ;

/* Variables and functions */
 struct i915_syncmap** __sync_child (struct i915_syncmap*) ; 
 unsigned int ffs (unsigned int) ; 
 int /*<<< orphan*/  kfree (struct i915_syncmap*) ; 

__attribute__((used)) static void __sync_free(struct i915_syncmap *p)
{
	if (p->height) {
		unsigned int i;

		while ((i = ffs(p->bitmap))) {
			p->bitmap &= ~0u << i;
			__sync_free(__sync_child(p)[i - 1]);
		}
	}

	kfree(p);
}