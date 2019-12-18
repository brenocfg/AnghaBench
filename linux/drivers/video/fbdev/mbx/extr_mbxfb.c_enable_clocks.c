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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKSLEEP ; 
 int /*<<< orphan*/  COREPLL ; 
 int CORE_PLL_EN ; 
 int Core_Pll_M (int) ; 
 int Core_Pll_N (int) ; 
 int Core_Pll_P (int) ; 
 int /*<<< orphan*/  DISPPLL ; 
 int DISP_PLL_EN ; 
 int Disp_Pll_M (int) ; 
 int Disp_Pll_N (int) ; 
 int Disp_Pll_P (int) ; 
 int /*<<< orphan*/  M24CLK ; 
 int /*<<< orphan*/  MBXCLK ; 
 int /*<<< orphan*/  MEMCLK ; 
 int MEMCLK_EN ; 
 int /*<<< orphan*/  PIXCLK ; 
 int /*<<< orphan*/  PIXCLKDIV ; 
 int /*<<< orphan*/  PIXCLKSRC ; 
 int PIXCLKSRC_PLL_1 ; 
 int PIXCLK_EN ; 
 int /*<<< orphan*/  SDCLK ; 
 int SDCLK_EN ; 
 int /*<<< orphan*/  SYSCLKSRC ; 
 int SYSCLKSRC_PLL_2 ; 
 int /*<<< orphan*/  VOVRCLK ; 
 int /*<<< orphan*/  write_reg_dly (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_clocks(struct fb_info *fbi)
{
	/* enable clocks */
	write_reg_dly(SYSCLKSRC_PLL_2, SYSCLKSRC);
	write_reg_dly(PIXCLKSRC_PLL_1, PIXCLKSRC);
	write_reg_dly(0x00000000, CLKSLEEP);

	/* PLL output = (Frefclk * M) / (N * 2^P )
	 *
	 * M: 0x17, N: 0x3, P: 0x0 == 100 Mhz!
	 * M: 0xb, N: 0x1, P: 0x1 == 71 Mhz
	 * */
	write_reg_dly((Core_Pll_M(0xb) | Core_Pll_N(0x1) | Core_Pll_P(0x1) |
		CORE_PLL_EN),
	       COREPLL);

	write_reg_dly((Disp_Pll_M(0x1b) | Disp_Pll_N(0x7) | Disp_Pll_P(0x1) |
		DISP_PLL_EN),
	       DISPPLL);

	write_reg_dly(0x00000000, VOVRCLK);
	write_reg_dly(PIXCLK_EN, PIXCLK);
	write_reg_dly(MEMCLK_EN, MEMCLK);
	write_reg_dly(0x00000001, M24CLK);
	write_reg_dly(0x00000001, MBXCLK);
	write_reg_dly(SDCLK_EN, SDCLK);
	write_reg_dly(0x00000001, PIXCLKDIV);
}