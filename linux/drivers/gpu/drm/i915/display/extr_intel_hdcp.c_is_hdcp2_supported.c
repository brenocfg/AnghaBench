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
 int /*<<< orphan*/  CONFIG_INTEL_MEI_HDCP ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 

__attribute__((used)) static bool is_hdcp2_supported(struct drm_i915_private *dev_priv)
{
	if (!IS_ENABLED(CONFIG_INTEL_MEI_HDCP))
		return false;

	return (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv) ||
		IS_KABYLAKE(dev_priv));
}