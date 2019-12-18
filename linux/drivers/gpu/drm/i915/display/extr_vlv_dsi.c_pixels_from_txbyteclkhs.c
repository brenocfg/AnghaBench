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
typedef  int u16 ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 

__attribute__((used)) static u16 pixels_from_txbyteclkhs(u16 clk_hs, int bpp, int lane_count,
			u16 burst_mode_ratio)
{
	return DIV_ROUND_UP((clk_hs * lane_count * 8 * 100),
						(bpp * burst_mode_ratio));
}