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
struct drm_i915_private {int /*<<< orphan*/ * chv_phy_assert; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum dpio_phy { ____Placeholder_dpio_phy } dpio_phy ;
typedef  enum dpio_channel { ____Placeholder_dpio_channel } dpio_channel ;

/* Variables and functions */
 int DPIO_ALLDL_POWERDOWN ; 
 int DPIO_ANYDL_POWERDOWN ; 
 int DPIO_ANYDL_POWERDOWN_SHIFT_CH0 ; 
 int DPIO_ANYDL_POWERDOWN_SHIFT_CH1 ; 
 int DPIO_CH0 ; 
 int DPIO_CH1 ; 
 int DPIO_PHY0 ; 
 int PIPE_A ; 
 int PIPE_C ; 
 int /*<<< orphan*/  WARN (int,char*,int,int,int,int,int,int) ; 
 int _CHV_CMN_DW0_CH0 ; 
 int _CHV_CMN_DW6_CH1 ; 
 int /*<<< orphan*/  vlv_dpio_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_dpio_put (struct drm_i915_private*) ; 
 int vlv_dpio_read (struct drm_i915_private*,int,int) ; 

__attribute__((used)) static void assert_chv_phy_powergate(struct drm_i915_private *dev_priv, enum dpio_phy phy,
				     enum dpio_channel ch, bool override, unsigned int mask)
{
	enum pipe pipe = phy == DPIO_PHY0 ? PIPE_A : PIPE_C;
	u32 reg, val, expected, actual;

	/*
	 * The BIOS can leave the PHY is some weird state
	 * where it doesn't fully power down some parts.
	 * Disable the asserts until the PHY has been fully
	 * reset (ie. the power well has been disabled at
	 * least once).
	 */
	if (!dev_priv->chv_phy_assert[phy])
		return;

	if (ch == DPIO_CH0)
		reg = _CHV_CMN_DW0_CH0;
	else
		reg = _CHV_CMN_DW6_CH1;

	vlv_dpio_get(dev_priv);
	val = vlv_dpio_read(dev_priv, pipe, reg);
	vlv_dpio_put(dev_priv);

	/*
	 * This assumes !override is only used when the port is disabled.
	 * All lanes should power down even without the override when
	 * the port is disabled.
	 */
	if (!override || mask == 0xf) {
		expected = DPIO_ALLDL_POWERDOWN | DPIO_ANYDL_POWERDOWN;
		/*
		 * If CH1 common lane is not active anymore
		 * (eg. for pipe B DPLL) the entire channel will
		 * shut down, which causes the common lane registers
		 * to read as 0. That means we can't actually check
		 * the lane power down status bits, but as the entire
		 * register reads as 0 it's a good indication that the
		 * channel is indeed entirely powered down.
		 */
		if (ch == DPIO_CH1 && val == 0)
			expected = 0;
	} else if (mask != 0x0) {
		expected = DPIO_ANYDL_POWERDOWN;
	} else {
		expected = 0;
	}

	if (ch == DPIO_CH0)
		actual = val >> DPIO_ANYDL_POWERDOWN_SHIFT_CH0;
	else
		actual = val >> DPIO_ANYDL_POWERDOWN_SHIFT_CH1;
	actual &= DPIO_ALLDL_POWERDOWN | DPIO_ANYDL_POWERDOWN;

	WARN(actual != expected,
	     "Unexpected DPIO lane power down: all %d, any %d. Expected: all %d, any %d. (0x%x = 0x%08x)\n",
	     !!(actual & DPIO_ALLDL_POWERDOWN), !!(actual & DPIO_ANYDL_POWERDOWN),
	     !!(expected & DPIO_ALLDL_POWERDOWN), !!(expected & DPIO_ANYDL_POWERDOWN),
	     reg, val);
}