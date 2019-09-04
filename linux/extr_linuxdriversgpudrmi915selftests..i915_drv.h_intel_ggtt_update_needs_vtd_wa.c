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

/* Variables and functions */
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ intel_vtd_active () ; 

__attribute__((used)) static inline bool
intel_ggtt_update_needs_vtd_wa(struct drm_i915_private *dev_priv)
{
	return IS_BROXTON(dev_priv) && intel_vtd_active();
}