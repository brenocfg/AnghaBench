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
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trash_stolen (struct drm_i915_private*) ; 

__attribute__((used)) static void simulate_hibernate(struct drm_i915_private *i915)
{
	intel_wakeref_t wakeref;

	wakeref = intel_runtime_pm_get(&i915->runtime_pm);

	/*
	 * As a final sting in the tail, invalidate stolen. Under a real S4,
	 * stolen is lost and needs to be refilled on resume. However, under
	 * CI we merely do S4-device testing (as full S4 is too unreliable
	 * for automated testing across a cluster), so to simulate the effect
	 * of stolen being trashed across S4, we trash it ourselves.
	 */
	trash_stolen(i915);

	intel_runtime_pm_put(&i915->runtime_pm, wakeref);
}