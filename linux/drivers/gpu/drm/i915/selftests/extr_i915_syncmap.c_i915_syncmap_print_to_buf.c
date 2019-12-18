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
 int /*<<< orphan*/  __sync_print (struct i915_syncmap*,char*,unsigned long*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
i915_syncmap_print_to_buf(struct i915_syncmap *p, char *buf, unsigned long sz)
{
	if (!p)
		return false;

	while (p->parent)
		p = p->parent;

	__sync_print(p, buf, &sz, 0, 1, 0);
	return true;
}