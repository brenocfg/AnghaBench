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
struct TYPE_2__ {int dc_state; } ;
struct drm_i915_private {TYPE_1__ csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_STATE_EN ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int gen9_dc_mask (struct drm_i915_private*) ; 

__attribute__((used)) static void gen9_sanitize_dc_state(struct drm_i915_private *dev_priv)
{
	u32 val;

	val = I915_READ(DC_STATE_EN) & gen9_dc_mask(dev_priv);

	DRM_DEBUG_KMS("Resetting DC state tracking from %02x to %02x\n",
		      dev_priv->csr.dc_state, val);
	dev_priv->csr.dc_state = val;
}