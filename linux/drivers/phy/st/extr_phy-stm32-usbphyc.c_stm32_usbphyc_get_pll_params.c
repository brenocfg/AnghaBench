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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pll_params {int /*<<< orphan*/  frac; int /*<<< orphan*/  ndiv; } ;

/* Variables and functions */
 unsigned long long HZ_PER_MHZ ; 
 scalar_t__ PLL_FVCO_MHZ ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 

__attribute__((used)) static void stm32_usbphyc_get_pll_params(u32 clk_rate,
					 struct pll_params *pll_params)
{
	unsigned long long fvco, ndiv, frac;

	/*    _
	 *   | FVCO = INFF*2*(NDIV + FRACT/2^16) when DITHER_DISABLE[1] = 1
	 *   | FVCO = 2880MHz
	 *  <
	 *   | NDIV = integer part of input bits to set the LDF
	 *   |_FRACT = fractional part of input bits to set the LDF
	 *  =>	PLLNDIV = integer part of (FVCO / (INFF*2))
	 *  =>	PLLFRACIN = fractional part of(FVCO / INFF*2) * 2^16
	 * <=>  PLLFRACIN = ((FVCO / (INFF*2)) - PLLNDIV) * 2^16
	 */
	fvco = (unsigned long long)PLL_FVCO_MHZ * HZ_PER_MHZ;

	ndiv = fvco;
	do_div(ndiv, (clk_rate * 2));
	pll_params->ndiv = (u8)ndiv;

	frac = fvco * (1 << 16);
	do_div(frac, (clk_rate * 2));
	frac = frac - (ndiv * (1 << 16));
	pll_params->frac = (u16)frac;
}