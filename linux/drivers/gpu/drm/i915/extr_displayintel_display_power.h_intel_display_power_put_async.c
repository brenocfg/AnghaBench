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
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_display_power_put_async (struct drm_i915_private*,int,int) ; 

__attribute__((used)) static inline void
intel_display_power_put_async(struct drm_i915_private *i915,
			      enum intel_display_power_domain domain,
			      intel_wakeref_t wakeref)
{
	__intel_display_power_put_async(i915, domain, -1);
}