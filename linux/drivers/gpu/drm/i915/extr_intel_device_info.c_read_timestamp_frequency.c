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
struct drm_i915_private {int rawclk_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTC_MODE ; 
 int CTC_SHIFT_PARAMETER_MASK ; 
 int CTC_SHIFT_PARAMETER_SHIFT ; 
 int CTC_SOURCE_DIVIDE_LOGIC ; 
 int CTC_SOURCE_PARAMETER_MASK ; 
 int GEN10_RPM_CONFIG0_CTC_SHIFT_PARAMETER_MASK ; 
 int GEN10_RPM_CONFIG0_CTC_SHIFT_PARAMETER_SHIFT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (char*) ; 
 int /*<<< orphan*/  RPM_CONFIG0 ; 
 int gen10_get_crystal_clock_freq (struct drm_i915_private*,int) ; 
 int gen11_get_crystal_clock_freq (struct drm_i915_private*,int) ; 
 int read_reference_ts_freq (struct drm_i915_private*) ; 

__attribute__((used)) static u32 read_timestamp_frequency(struct drm_i915_private *dev_priv)
{
	u32 f12_5_mhz = 12500;
	u32 f19_2_mhz = 19200;
	u32 f24_mhz = 24000;

	if (INTEL_GEN(dev_priv) <= 4) {
		/* PRMs say:
		 *
		 *     "The value in this register increments once every 16
		 *      hclks." (through the “Clocking Configuration”
		 *      (“CLKCFG”) MCHBAR register)
		 */
		return dev_priv->rawclk_freq / 16;
	} else if (INTEL_GEN(dev_priv) <= 8) {
		/* PRMs say:
		 *
		 *     "The PCU TSC counts 10ns increments; this timestamp
		 *      reflects bits 38:3 of the TSC (i.e. 80ns granularity,
		 *      rolling over every 1.5 hours).
		 */
		return f12_5_mhz;
	} else if (INTEL_GEN(dev_priv) <= 9) {
		u32 ctc_reg = I915_READ(CTC_MODE);
		u32 freq = 0;

		if ((ctc_reg & CTC_SOURCE_PARAMETER_MASK) == CTC_SOURCE_DIVIDE_LOGIC) {
			freq = read_reference_ts_freq(dev_priv);
		} else {
			freq = IS_GEN9_LP(dev_priv) ? f19_2_mhz : f24_mhz;

			/* Now figure out how the command stream's timestamp
			 * register increments from this frequency (it might
			 * increment only every few clock cycle).
			 */
			freq >>= 3 - ((ctc_reg & CTC_SHIFT_PARAMETER_MASK) >>
				      CTC_SHIFT_PARAMETER_SHIFT);
		}

		return freq;
	} else if (INTEL_GEN(dev_priv) <= 12) {
		u32 ctc_reg = I915_READ(CTC_MODE);
		u32 freq = 0;

		/* First figure out the reference frequency. There are 2 ways
		 * we can compute the frequency, either through the
		 * TIMESTAMP_OVERRIDE register or through RPM_CONFIG. CTC_MODE
		 * tells us which one we should use.
		 */
		if ((ctc_reg & CTC_SOURCE_PARAMETER_MASK) == CTC_SOURCE_DIVIDE_LOGIC) {
			freq = read_reference_ts_freq(dev_priv);
		} else {
			u32 rpm_config_reg = I915_READ(RPM_CONFIG0);

			if (INTEL_GEN(dev_priv) <= 10)
				freq = gen10_get_crystal_clock_freq(dev_priv,
								rpm_config_reg);
			else
				freq = gen11_get_crystal_clock_freq(dev_priv,
								rpm_config_reg);

			/* Now figure out how the command stream's timestamp
			 * register increments from this frequency (it might
			 * increment only every few clock cycle).
			 */
			freq >>= 3 - ((rpm_config_reg &
				       GEN10_RPM_CONFIG0_CTC_SHIFT_PARAMETER_MASK) >>
				      GEN10_RPM_CONFIG0_CTC_SHIFT_PARAMETER_SHIFT);
		}

		return freq;
	}

	MISSING_CASE("Unknown gen, unable to read command streamer timestamp frequency\n");
	return 0;
}