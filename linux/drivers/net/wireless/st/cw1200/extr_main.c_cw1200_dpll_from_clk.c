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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int) ; 

u32 cw1200_dpll_from_clk(u16 clk_khz)
{
	switch (clk_khz) {
	case 0x32C8: /* 13000 KHz */
		return 0x1D89D241;
	case 0x3E80: /* 16000 KHz */
		return 0x000001E1;
	case 0x41A0: /* 16800 KHz */
		return 0x124931C1;
	case 0x4B00: /* 19200 KHz */
		return 0x00000191;
	case 0x5DC0: /* 24000 KHz */
		return 0x00000141;
	case 0x6590: /* 26000 KHz */
		return 0x0EC4F121;
	case 0x8340: /* 33600 KHz */
		return 0x092490E1;
	case 0x9600: /* 38400 KHz */
		return 0x100010C1;
	case 0x9C40: /* 40000 KHz */
		return 0x000000C1;
	case 0xBB80: /* 48000 KHz */
		return 0x000000A1;
	case 0xCB20: /* 52000 KHz */
		return 0x07627091;
	default:
		pr_err("Unknown Refclk freq (0x%04x), using 26000KHz\n",
		       clk_khz);
		return 0x0EC4F121;
	}
}