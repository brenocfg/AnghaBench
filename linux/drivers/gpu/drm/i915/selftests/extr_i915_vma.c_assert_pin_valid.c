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
struct pin_mode {int /*<<< orphan*/  flags; int /*<<< orphan*/  size; } ;
struct i915_vma {int dummy; } ;

/* Variables and functions */
 scalar_t__ i915_vma_misplaced (struct i915_vma const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool assert_pin_valid(const struct i915_vma *vma,
			     const struct pin_mode *mode,
			     int result)
{
	if (result)
		return false;

	if (i915_vma_misplaced(vma, mode->size, 0, mode->flags))
		return false;

	return true;
}