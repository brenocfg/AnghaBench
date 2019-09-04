#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {size_t high_mclk_index; size_t medium_mclk_index; size_t low_mclk_index; int /*<<< orphan*/ * mclks; } ;
struct rv6xx_power_info {int /*<<< orphan*/  fb_div_scale; TYPE_3__ hw; scalar_t__ mclk_ss; } ;
struct TYPE_4__ {int reference_freq; } ;
struct TYPE_5__ {TYPE_1__ mpll; } ;
struct radeon_device {TYPE_2__ clock; } ;
struct radeon_atom_ss {int /*<<< orphan*/  rate; int /*<<< orphan*/  percentage; } ;
struct atom_clock_dividers {int ref_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_INTERNAL_MEMORY_SS ; 
 scalar_t__ radeon_atombios_get_asic_ss_info (struct radeon_device*,struct radeon_atom_ss*,int /*<<< orphan*/ ,int) ; 
 int rv6xx_calculate_spread_spectrum_clk_s (int /*<<< orphan*/ ,int) ; 
 int rv6xx_calculate_spread_spectrum_clk_v (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv6xx_enable_memory_spread_spectrum (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_find_memory_clock_with_highest_vco (struct radeon_device*,int /*<<< orphan*/ ,int,struct atom_clock_dividers*,int*) ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_set_memory_spread_spectrum_clk_s (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_set_memory_spread_spectrum_clk_v (struct radeon_device*,int) ; 

__attribute__((used)) static void rv6xx_program_mclk_spread_spectrum_parameters(struct radeon_device *rdev)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);
	u32 ref_clk = rdev->clock.mpll.reference_freq;
	struct atom_clock_dividers dividers;
	struct radeon_atom_ss ss;
	u32 vco_freq = 0, clk_v, clk_s;

	rv6xx_enable_memory_spread_spectrum(rdev, false);

	if (pi->mclk_ss) {
		rv6xx_find_memory_clock_with_highest_vco(rdev,
							 pi->hw.mclks[pi->hw.high_mclk_index],
							 ref_clk,
							 &dividers,
							 &vco_freq);

		rv6xx_find_memory_clock_with_highest_vco(rdev,
							 pi->hw.mclks[pi->hw.medium_mclk_index],
							 ref_clk,
							 &dividers,
							 &vco_freq);

		rv6xx_find_memory_clock_with_highest_vco(rdev,
							 pi->hw.mclks[pi->hw.low_mclk_index],
							 ref_clk,
							 &dividers,
							 &vco_freq);

		if (vco_freq) {
			if (radeon_atombios_get_asic_ss_info(rdev, &ss,
							     ASIC_INTERNAL_MEMORY_SS, vco_freq)) {
				clk_v = rv6xx_calculate_spread_spectrum_clk_v(vco_freq,
									     (ref_clk / (dividers.ref_div + 1)),
									     ss.rate,
									     ss.percentage,
									     pi->fb_div_scale);

				clk_s = rv6xx_calculate_spread_spectrum_clk_s(ss.rate,
									     (ref_clk / (dividers.ref_div + 1)));

				rv6xx_set_memory_spread_spectrum_clk_v(rdev, clk_v);
				rv6xx_set_memory_spread_spectrum_clk_s(rdev, clk_s);
				rv6xx_enable_memory_spread_spectrum(rdev, true);
			}
		}
	}
}