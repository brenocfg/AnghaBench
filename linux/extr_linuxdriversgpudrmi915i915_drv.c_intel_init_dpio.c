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
typedef  int /*<<< orphan*/  DPIO_PHY_IOSF_PORT ;

/* Variables and functions */
 int /*<<< orphan*/  IOSF_PORT_DPIO ; 
 int /*<<< orphan*/  IOSF_PORT_DPIO_2 ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 

__attribute__((used)) static void intel_init_dpio(struct drm_i915_private *dev_priv)
{
	/*
	 * IOSF_PORT_DPIO is used for VLV x2 PHY (DP/HDMI B and C),
	 * CHV x1 PHY (DP/HDMI D)
	 * IOSF_PORT_DPIO_2 is used for CHV x2 PHY (DP/HDMI B and C)
	 */
	if (IS_CHERRYVIEW(dev_priv)) {
		DPIO_PHY_IOSF_PORT(DPIO_PHY0) = IOSF_PORT_DPIO_2;
		DPIO_PHY_IOSF_PORT(DPIO_PHY1) = IOSF_PORT_DPIO;
	} else if (IS_VALLEYVIEW(dev_priv)) {
		DPIO_PHY_IOSF_PORT(DPIO_PHY0) = IOSF_PORT_DPIO;
	}
}