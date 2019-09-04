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
struct i915_syncmap {int /*<<< orphan*/  height; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 

__attribute__((used)) static inline struct i915_syncmap **__sync_child(struct i915_syncmap *p)
{
	GEM_BUG_ON(!p->height);
	return (struct i915_syncmap **)(p + 1);
}