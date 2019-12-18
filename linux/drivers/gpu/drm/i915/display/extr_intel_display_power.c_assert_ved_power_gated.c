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
 int /*<<< orphan*/  PUNIT_REG_VEDSSPM0 ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  vlv_punit_is_power_gated (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void assert_ved_power_gated(struct drm_i915_private *dev_priv)
{
	WARN(!vlv_punit_is_power_gated(dev_priv, PUNIT_REG_VEDSSPM0),
	     "VED not power gated\n");
}