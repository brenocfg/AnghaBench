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
struct i915_syncmap {struct i915_syncmap* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sync_free (struct i915_syncmap*) ; 

void i915_syncmap_free(struct i915_syncmap **root)
{
	struct i915_syncmap *p;

	p = *root;
	if (!p)
		return;

	while (p->parent)
		p = p->parent;

	__sync_free(p);
	*root = NULL;
}