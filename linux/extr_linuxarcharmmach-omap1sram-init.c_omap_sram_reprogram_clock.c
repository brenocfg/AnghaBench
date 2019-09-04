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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  _omap_sram_reprogram_clock (int,int) ; 
 scalar_t__ cpu_is_omap7xx () ; 

void omap_sram_reprogram_clock(u32 dpllctl, u32 ckctl)
{
	BUG_ON(!_omap_sram_reprogram_clock);
	/* On 730, bit 13 must always be 1 */
	if (cpu_is_omap7xx())
		ckctl |= 0x2000;
	_omap_sram_reprogram_clock(dpllctl, ckctl);
}