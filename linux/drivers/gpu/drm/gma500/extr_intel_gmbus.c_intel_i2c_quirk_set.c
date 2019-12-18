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
struct drm_psb_private {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void intel_i2c_quirk_set(struct drm_psb_private *dev_priv, bool enable)
{
	/* When using bit bashing for I2C, this bit needs to be set to 1 */
	/* FIXME: We are never Pineview, right?

	u32 val;

	if (!IS_PINEVIEW(dev_priv->dev))
		return;

	val = REG_READ(DSPCLK_GATE_D);
	if (enable)
		val |= DPCUNIT_CLOCK_GATE_DISABLE;
	else
		val &= ~DPCUNIT_CLOCK_GATE_DISABLE;
	REG_WRITE(DSPCLK_GATE_D, val);

	return;
	*/
}