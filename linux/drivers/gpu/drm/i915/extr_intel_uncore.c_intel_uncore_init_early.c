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
struct intel_uncore {int /*<<< orphan*/ * debug; int /*<<< orphan*/ * rpm; struct drm_i915_private* i915; int /*<<< orphan*/  lock; } ;
struct drm_i915_private {int /*<<< orphan*/  mmio_debug; int /*<<< orphan*/  runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void intel_uncore_init_early(struct intel_uncore *uncore,
			     struct drm_i915_private *i915)
{
	spin_lock_init(&uncore->lock);
	uncore->i915 = i915;
	uncore->rpm = &i915->runtime_pm;
	uncore->debug = &i915->mmio_debug;
}