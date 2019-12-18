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
typedef  int u8 ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad9389b_wr_and_or (struct v4l2_subdev*,int,int,int) ; 

__attribute__((used)) static void ad9389b_set_manual_pll_gear(struct v4l2_subdev *sd, u32 pixelclock)
{
	u8 gear;

	/* Workaround for TMDS PLL problem
	 * The TMDS PLL in AD9389b change gear when the chip is heated above a
	 * certain temperature. The output is disabled when the PLL change gear
	 * so the monitor has to lock on the signal again. A workaround for
	 * this is to use the manual PLL gears. This is a solution from Analog
	 * Devices that is not documented in the datasheets.
	 * 0x98 [7] = enable manual gearing. 0x98 [6:4] = gear
	 *
	 * The pixel frequency ranges are based on readout of the gear the
	 * automatic gearing selects for different pixel clocks
	 * (read from 0x9e [3:1]).
	 */

	if (pixelclock > 140000000)
		gear = 0xc0; /* 4th gear */
	else if (pixelclock > 117000000)
		gear = 0xb0; /* 3rd gear */
	else if (pixelclock > 87000000)
		gear = 0xa0; /* 2nd gear */
	else if (pixelclock > 60000000)
		gear = 0x90; /* 1st gear */
	else
		gear = 0x80; /* 0th gear */

	ad9389b_wr_and_or(sd, 0x98, 0x0f, gear);
}