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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int DREF_NONSPREAD_SOURCE_MASK ; 
 int DREF_SSC_SOURCE_MASK ; 
 int DREF_SUPERSPREAD_SOURCE_MASK ; 
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_STATE_WARN (int,char*) ; 
 int /*<<< orphan*/  I915_STATE_WARN_ON (int) ; 
 int /*<<< orphan*/  PCH_DREF_CONTROL ; 

__attribute__((used)) static void ibx_assert_pch_refclk_enabled(struct drm_i915_private *dev_priv)
{
	u32 val;
	bool enabled;

	I915_STATE_WARN_ON(!(HAS_PCH_IBX(dev_priv) || HAS_PCH_CPT(dev_priv)));

	val = I915_READ(PCH_DREF_CONTROL);
	enabled = !!(val & (DREF_SSC_SOURCE_MASK | DREF_NONSPREAD_SOURCE_MASK |
			    DREF_SUPERSPREAD_SOURCE_MASK));
	I915_STATE_WARN(!enabled, "PCH refclk assertion failure, should be active but is disabled\n");
}