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
struct i915_power_well {int dummy; } ;
struct TYPE_2__ {int allowed_dc_mask; int /*<<< orphan*/  dmc_payload; } ;
struct drm_i915_private {TYPE_1__ csr; } ;

/* Variables and functions */
 int DC_STATE_EN_UPTO_DC5 ; 
 int DC_STATE_EN_UPTO_DC6 ; 
 int /*<<< orphan*/  gen9_enable_dc5 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  skl_enable_dc6 (struct drm_i915_private*) ; 

__attribute__((used)) static void gen9_dc_off_power_well_disable(struct drm_i915_private *dev_priv,
					   struct i915_power_well *power_well)
{
	if (!dev_priv->csr.dmc_payload)
		return;

	if (dev_priv->csr.allowed_dc_mask & DC_STATE_EN_UPTO_DC6)
		skl_enable_dc6(dev_priv);
	else if (dev_priv->csr.allowed_dc_mask & DC_STATE_EN_UPTO_DC5)
		gen9_enable_dc5(dev_priv);
}