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
 int /*<<< orphan*/  LPC18XX_PLL0_MSEL_MAX ; 

__attribute__((used)) static u32 lpc18xx_pll0_mdec2msel(u32 x)
{
	int i;

	switch (x) {
	case 0x18003: return 1;
	case 0x10003: return 2;
	default:
		for (i = LPC18XX_PLL0_MSEL_MAX + 1; x != 0x4000 && i > 0; i--)
			x = ((x ^ x >> 14) & 1) | (x << 1 & 0x7fff);
		return i;
	}
}