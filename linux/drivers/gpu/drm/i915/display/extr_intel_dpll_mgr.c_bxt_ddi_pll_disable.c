#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_shared_dpll {TYPE_1__* info; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_PORT_PLL_ENABLE (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int PORT_PLL_ENABLE ; 
 int PORT_PLL_POWER_ENABLE ; 
 int PORT_PLL_POWER_STATE ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_us (int,int) ; 

__attribute__((used)) static void bxt_ddi_pll_disable(struct drm_i915_private *dev_priv,
					struct intel_shared_dpll *pll)
{
	enum port port = (enum port)pll->info->id; /* 1:1 port->PLL mapping */
	u32 temp;

	temp = I915_READ(BXT_PORT_PLL_ENABLE(port));
	temp &= ~PORT_PLL_ENABLE;
	I915_WRITE(BXT_PORT_PLL_ENABLE(port), temp);
	POSTING_READ(BXT_PORT_PLL_ENABLE(port));

	if (IS_GEMINILAKE(dev_priv)) {
		temp = I915_READ(BXT_PORT_PLL_ENABLE(port));
		temp &= ~PORT_PLL_POWER_ENABLE;
		I915_WRITE(BXT_PORT_PLL_ENABLE(port), temp);

		if (wait_for_us(!(I915_READ(BXT_PORT_PLL_ENABLE(port)) &
				PORT_PLL_POWER_STATE), 200))
			DRM_ERROR("Power state not reset for PLL:%d\n", port);
	}
}