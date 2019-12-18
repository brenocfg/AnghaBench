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
struct drm_i915_private {int /*<<< orphan*/  sb_qos; } ;

/* Variables and functions */
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  iosf_mbi_punit_acquire () ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ping ; 
 int /*<<< orphan*/  pm_qos_update_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __vlv_punit_get(struct drm_i915_private *i915)
{
	iosf_mbi_punit_acquire();

	/*
	 * Prevent the cpu from sleeping while we use this sideband, otherwise
	 * the punit may cause a machine hang. The issue appears to be isolated
	 * with changing the power state of the CPU package while changing
	 * the power state via the punit, and we have only observed it
	 * reliably on 4-core Baytail systems suggesting the issue is in the
	 * power delivery mechanism and likely to be be board/function
	 * specific. Hence we presume the workaround needs only be applied
	 * to the Valleyview P-unit and not all sideband communications.
	 */
	if (IS_VALLEYVIEW(i915)) {
		pm_qos_update_request(&i915->sb_qos, 0);
		on_each_cpu(ping, NULL, 1);
	}
}