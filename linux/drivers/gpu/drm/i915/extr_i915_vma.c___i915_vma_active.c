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
struct i915_active {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  active_to_vma (struct i915_active*) ; 
 scalar_t__ i915_vma_tryget (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __i915_vma_active(struct i915_active *ref)
{
	return i915_vma_tryget(active_to_vma(ref)) ? 0 : -ENOENT;
}