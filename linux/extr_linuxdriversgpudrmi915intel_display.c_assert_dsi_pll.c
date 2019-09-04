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
struct drm_i915_private {int /*<<< orphan*/  sb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_REG_DSI_PLL_CONTROL ; 
 int DSI_PLL_VCO_EN ; 
 int /*<<< orphan*/  I915_STATE_WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onoff (int) ; 
 int vlv_cck_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

void assert_dsi_pll(struct drm_i915_private *dev_priv, bool state)
{
	u32 val;
	bool cur_state;

	mutex_lock(&dev_priv->sb_lock);
	val = vlv_cck_read(dev_priv, CCK_REG_DSI_PLL_CONTROL);
	mutex_unlock(&dev_priv->sb_lock);

	cur_state = val & DSI_PLL_VCO_EN;
	I915_STATE_WARN(cur_state != state,
	     "DSI PLL state assertion failure (expected %s, current %s)\n",
			onoff(state), onoff(cur_state));
}