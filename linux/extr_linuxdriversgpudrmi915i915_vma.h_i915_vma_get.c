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
struct i915_vma {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_object_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct i915_vma *i915_vma_get(struct i915_vma *vma)
{
	i915_gem_object_get(vma->obj);
	return vma;
}