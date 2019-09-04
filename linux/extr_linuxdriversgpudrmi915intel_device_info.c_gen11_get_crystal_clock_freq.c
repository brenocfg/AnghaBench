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
#define  GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_19_2_MHZ 131 
#define  GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_24_MHZ 130 
#define  GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_25_MHZ 129 
#define  GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_38_4_MHZ 128 
 int GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_MASK ; 
 int GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_SHIFT ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 

__attribute__((used)) static u32 gen11_get_crystal_clock_freq(struct drm_i915_private *dev_priv,
					u32 rpm_config_reg)
{
	u32 f19_2_mhz = 19200;
	u32 f24_mhz = 24000;
	u32 f25_mhz = 25000;
	u32 f38_4_mhz = 38400;
	u32 crystal_clock = (rpm_config_reg &
			     GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_MASK) >>
			    GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_SHIFT;

	switch (crystal_clock) {
	case GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_24_MHZ:
		return f24_mhz;
	case GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_19_2_MHZ:
		return f19_2_mhz;
	case GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_38_4_MHZ:
		return f38_4_mhz;
	case GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_25_MHZ:
		return f25_mhz;
	default:
		MISSING_CASE(crystal_clock);
		return 0;
	}
}