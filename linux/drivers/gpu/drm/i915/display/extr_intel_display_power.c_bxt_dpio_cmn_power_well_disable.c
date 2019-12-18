#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i915_power_well {TYPE_2__* desc; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  phy; } ;
struct TYPE_4__ {TYPE_1__ bxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxt_ddi_phy_uninit (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bxt_dpio_cmn_power_well_disable(struct drm_i915_private *dev_priv,
					    struct i915_power_well *power_well)
{
	bxt_ddi_phy_uninit(dev_priv, power_well->desc->bxt.phy);
}