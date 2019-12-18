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
struct pll_values {int div_r0; int div_f0; int div_q0; int div_r1; int div_f1; int div_q1; void* range1; void* range0; } ;

/* Variables and functions */
 int abs (int const) ; 
 void* ufx_calc_range (int) ; 

__attribute__((used)) static void ufx_calc_pll_values(const u32 clk_pixel_pll, struct pll_values *asic_pll)
{
	const u32 ref_clk = 25000000;
	u32 div_r0, div_f0, div_q0, div_r1, div_f1, div_q1;
	u32 min_error = clk_pixel_pll;

	for (div_r0 = 1; div_r0 <= 32; div_r0++) {
		u32 ref_freq0 = ref_clk / div_r0;
		if (ref_freq0 < 5000000)
			break;

		if (ref_freq0 > 200000000)
			continue;

		for (div_f0 = 1; div_f0 <= 256; div_f0++) {
			u32 vco_freq0 = ref_freq0 * div_f0;

			if (vco_freq0 < 350000000)
				continue;

			if (vco_freq0 > 700000000)
				break;

			for (div_q0 = 0; div_q0 < 7; div_q0++) {
				u32 pllout_freq0 = vco_freq0 / (1 << div_q0);

				if (pllout_freq0 < 5000000)
					break;

				if (pllout_freq0 > 200000000)
					continue;

				for (div_r1 = 1; div_r1 <= 32; div_r1++) {
					u32 ref_freq1 = pllout_freq0 / div_r1;

					if (ref_freq1 < 5000000)
						break;

					for (div_f1 = 1; div_f1 <= 256; div_f1++) {
						u32 vco_freq1 = ref_freq1 * div_f1;

						if (vco_freq1 < 350000000)
							continue;

						if (vco_freq1 > 700000000)
							break;

						for (div_q1 = 0; div_q1 < 7; div_q1++) {
							u32 pllout_freq1 = vco_freq1 / (1 << div_q1);
							int error = abs(pllout_freq1 - clk_pixel_pll);

							if (pllout_freq1 < 5000000)
								break;

							if (pllout_freq1 > 700000000)
								continue;

							if (error < min_error) {
								min_error = error;

								/* final returned value is equal to calculated value - 1
								 * because a value of 0 = divide by 1 */
								asic_pll->div_r0 = div_r0 - 1;
								asic_pll->div_f0 = div_f0 - 1;
								asic_pll->div_q0 = div_q0;
								asic_pll->div_r1 = div_r1 - 1;
								asic_pll->div_f1 = div_f1 - 1;
								asic_pll->div_q1 = div_q1;

								asic_pll->range0 = ufx_calc_range(ref_freq0);
								asic_pll->range1 = ufx_calc_range(ref_freq1);

								if (min_error == 0)
									return;
							}
						}
					}
				}
			}
		}
	}
}