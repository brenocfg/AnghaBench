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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int ATOM_EXT_PLL1 ; 
 scalar_t__ ENCODER_MODE_IS_DP (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_pixel_clock_source_from_pll(u32 encoder_mode, int pll_id)
{
	if (ENCODER_MODE_IS_DP(encoder_mode)) {
		if (pll_id < ATOM_EXT_PLL1)
			return true;
		else
			return false;
	} else {
		return true;
	}
}