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
struct intel_overlay {int /*<<< orphan*/  last_flip; } ;

/* Variables and functions */
 int i915_active_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_overlay_recover_from_interrupt(struct intel_overlay *overlay)
{
	return i915_active_wait(&overlay->last_flip);
}