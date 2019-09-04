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
typedef  size_t u32 ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t const*) ; 
 size_t GRF_SIDDQ ; 
#define  GRF_UOC0_CON0 130 
#define  GRF_UOC1_CON0 129 
#define  GRF_UOC2_CON0 128 
 int /*<<< orphan*/  grf_regmap ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,size_t const,size_t*) ; 

__attribute__((used)) static bool rk3288_slp_disable_osc(void)
{
	static const u32 reg_offset[] = { GRF_UOC0_CON0, GRF_UOC1_CON0,
					  GRF_UOC2_CON0 };
	u32 reg, i;

	/*
	 * if any usb phy is still on(GRF_SIDDQ==0), that means we need the
	 * function of usb wakeup, so do not switch to 32khz, since the usb phy
	 * clk does not connect to 32khz osc
	 */
	for (i = 0; i < ARRAY_SIZE(reg_offset); i++) {
		regmap_read(grf_regmap, reg_offset[i], &reg);
		if (!(reg & GRF_SIDDQ))
			return false;
	}

	return true;
}