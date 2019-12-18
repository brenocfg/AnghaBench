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
struct TYPE_2__ {int allowed_dc_mask; int dc_state; } ;
struct drm_i915_private {TYPE_1__ csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_STATE_EN ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int gen9_dc_mask (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_write_dc_state (struct drm_i915_private*,int) ; 

__attribute__((used)) static void gen9_set_dc_state(struct drm_i915_private *dev_priv, u32 state)
{
	u32 val;
	u32 mask;

	if (WARN_ON_ONCE(state & ~dev_priv->csr.allowed_dc_mask))
		state &= dev_priv->csr.allowed_dc_mask;

	val = I915_READ(DC_STATE_EN);
	mask = gen9_dc_mask(dev_priv);
	DRM_DEBUG_KMS("Setting DC state from %02x to %02x\n",
		      val & mask, state);

	/* Check if DMC is ignoring our DC state requests */
	if ((val & mask) != dev_priv->csr.dc_state)
		DRM_ERROR("DC state mismatch (0x%x -> 0x%x)\n",
			  dev_priv->csr.dc_state, val & mask);

	val &= ~mask;
	val |= state;

	gen9_write_dc_state(dev_priv, val);

	dev_priv->csr.dc_state = val & mask;
}