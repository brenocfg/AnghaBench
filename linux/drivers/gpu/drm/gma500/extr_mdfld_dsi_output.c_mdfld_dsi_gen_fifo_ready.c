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
typedef  scalar_t__ u32 ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__) ; 
 scalar_t__ GEN_FB_TIME_OUT ; 
 scalar_t__ REG_READ (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

void mdfld_dsi_gen_fifo_ready(struct drm_device *dev, u32 gen_fifo_stat_reg,
							u32 fifo_stat)
{
	u32 GEN_BF_time_out_count;

	/* Check MIPI Adatper command registers */
	for (GEN_BF_time_out_count = 0;
			GEN_BF_time_out_count < GEN_FB_TIME_OUT;
			GEN_BF_time_out_count++) {
		if ((REG_READ(gen_fifo_stat_reg) & fifo_stat) == fifo_stat)
			break;
		udelay(100);
	}

	if (GEN_BF_time_out_count == GEN_FB_TIME_OUT)
		DRM_ERROR("mdfld_dsi_gen_fifo_ready, Timeout. gen_fifo_stat_reg = 0x%x.\n",
					gen_fifo_stat_reg);
}