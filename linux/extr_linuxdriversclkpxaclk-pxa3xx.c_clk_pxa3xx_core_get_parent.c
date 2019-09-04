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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PXA_CORE_60Mhz ; 
 int /*<<< orphan*/  PXA_CORE_RUN ; 
 int /*<<< orphan*/  PXA_CORE_TURBO ; 
 scalar_t__ pxa3xx_is_ring_osc_forced () ; 

__attribute__((used)) static u8 clk_pxa3xx_core_get_parent(struct clk_hw *hw)
{
	unsigned long xclkcfg;
	unsigned int t;

	if (pxa3xx_is_ring_osc_forced())
		return PXA_CORE_60Mhz;

	/* Read XCLKCFG register turbo bit */
	__asm__ __volatile__("mrc\tp14, 0, %0, c6, c0, 0" : "=r"(xclkcfg));
	t = xclkcfg & 0x1;

	if (t)
		return PXA_CORE_TURBO;
	return PXA_CORE_RUN;
}