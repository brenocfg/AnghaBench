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
struct i915_gem_context {scalar_t__ timeline; } ;

/* Variables and functions */
 int /*<<< orphan*/  __assign_timeline (struct i915_gem_context*,scalar_t__) ; 

__attribute__((used)) static int clone_timeline(struct i915_gem_context *dst,
			  struct i915_gem_context *src)
{
	if (src->timeline)
		__assign_timeline(dst, src->timeline);

	return 0;
}