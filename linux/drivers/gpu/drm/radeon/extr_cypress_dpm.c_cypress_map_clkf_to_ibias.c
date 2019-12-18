#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int reference_freq; } ;
struct TYPE_4__ {TYPE_1__ mpll; } ;
struct radeon_device {TYPE_2__ clock; } ;

/* Variables and functions */

u32 cypress_map_clkf_to_ibias(struct radeon_device *rdev, u32 clkf)
{
	u32 ref_clk = rdev->clock.mpll.reference_freq;
	u32 vco = clkf * ref_clk;

	/* 100 Mhz ref clk */
	if (ref_clk == 10000) {
		if (vco > 500000)
			return 0xC6;
		if (vco > 400000)
			return 0x9D;
		if (vco > 330000)
			return 0x6C;
		if (vco > 250000)
			return 0x2B;
		if (vco >  160000)
			return 0x5B;
		if (vco > 120000)
			return 0x0A;
		return 0x4B;
	}

	/* 27 Mhz ref clk */
	if (vco > 250000)
		return 0x8B;
	if (vco > 200000)
		return 0xCC;
	if (vco > 150000)
		return 0x9B;
	return 0x6B;
}