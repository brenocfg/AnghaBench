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
struct igt_spinner {int /*<<< orphan*/  hws; int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_object_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igt_spinner_end (struct igt_spinner*) ; 

void igt_spinner_fini(struct igt_spinner *spin)
{
	igt_spinner_end(spin);

	i915_gem_object_unpin_map(spin->obj);
	i915_gem_object_put(spin->obj);

	i915_gem_object_unpin_map(spin->hws);
	i915_gem_object_put(spin->hws);
}