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

/* Variables and functions */
 int LPC18XX_PLL0_MSEL_MAX ; 

__attribute__((used)) static u32 lpc18xx_pll0_msel2mdec(u32 msel)
{
	u32 i, x = 0x4000;

	switch (msel) {
	case 0: return 0;
	case 1: return 0x18003;
	case 2: return 0x10003;
	default:
		for (i = msel; i <= LPC18XX_PLL0_MSEL_MAX; i++)
			x = ((x ^ x >> 1) & 1) << 14 | (x >> 1 & 0xffff);
		return x;
	}
}