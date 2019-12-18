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
struct radeon_encoder_tv_dac {int ps2_tvdac_adj; int pal_tvdac_adj; int ntsc_tvdac_adj; } ;
struct radeon_device {size_t family; int flags; } ;

/* Variables and functions */
 size_t CHIP_RV250 ; 
 int RADEON_IS_MOBILITY ; 
 int* default_tvdac_adj ; 

__attribute__((used)) static void radeon_legacy_get_tv_dac_info_from_table(struct radeon_device *rdev,
						     struct radeon_encoder_tv_dac *tv_dac)
{
	tv_dac->ps2_tvdac_adj = default_tvdac_adj[rdev->family];
	if ((rdev->flags & RADEON_IS_MOBILITY) && (rdev->family == CHIP_RV250))
		tv_dac->ps2_tvdac_adj = 0x00880000;
	tv_dac->pal_tvdac_adj = tv_dac->ps2_tvdac_adj;
	tv_dac->ntsc_tvdac_adj = tv_dac->ps2_tvdac_adj;
	return;
}