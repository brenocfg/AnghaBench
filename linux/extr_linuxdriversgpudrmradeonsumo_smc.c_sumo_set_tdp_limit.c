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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int RCU_SclkDpmTdpLimit01 ; 
 int RCU_SclkDpmTdpLimit23 ; 
 int RCU_SclkDpmTdpLimit47 ; 
 int RREG32_RCU (int) ; 
 int /*<<< orphan*/  WREG32_RCU (int,int) ; 

void sumo_set_tdp_limit(struct radeon_device *rdev, u32 index, u32 tdp_limit)
{
	u32 regoffset = 0;
	u32 shift = 0;
	u32 mask = 0xFFF;
	u32 sclk_dpm_tdp_limit;

	switch (index) {
	case 0:
		regoffset = RCU_SclkDpmTdpLimit01;
		shift = 16;
		break;
	case 1:
		regoffset = RCU_SclkDpmTdpLimit01;
		shift = 0;
		break;
	case 2:
		regoffset = RCU_SclkDpmTdpLimit23;
		shift = 16;
		break;
	case 3:
		regoffset = RCU_SclkDpmTdpLimit23;
		shift = 0;
		break;
	case 4:
		regoffset = RCU_SclkDpmTdpLimit47;
		shift = 16;
		break;
	case 7:
		regoffset = RCU_SclkDpmTdpLimit47;
		shift = 0;
		break;
	default:
		break;
	}

	sclk_dpm_tdp_limit = RREG32_RCU(regoffset);
	sclk_dpm_tdp_limit &= ~(mask << shift);
	sclk_dpm_tdp_limit |= (tdp_limit << shift);
	WREG32_RCU(regoffset, sclk_dpm_tdp_limit);
}