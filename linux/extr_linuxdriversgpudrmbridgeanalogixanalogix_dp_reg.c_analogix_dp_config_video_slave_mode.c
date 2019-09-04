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
struct TYPE_4__ {int interlaced; int v_sync_polarity; int h_sync_polarity; } ;
struct analogix_dp_device {scalar_t__ reg_base; TYPE_2__ video_info; TYPE_1__* plat_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_type; } ;

/* Variables and functions */
 scalar_t__ ANALOGIX_DP_FUNC_EN_1 ; 
 scalar_t__ ANALOGIX_DP_SOC_GENERAL_CTL ; 
 scalar_t__ ANALOGIX_DP_VIDEO_CTL_10 ; 
 int AUDIO_MODE_SPDIF_MODE ; 
 int HSYNC_POLARITY_CFG ; 
 int INTERACE_SCAN_CFG ; 
 int MASTER_VID_FUNC_EN_N ; 
 int RK_VID_CAP_FUNC_EN_N ; 
 int RK_VID_FIFO_FUNC_EN_N ; 
 int SLAVE_VID_FUNC_EN_N ; 
 int VIDEO_MODE_SLAVE_MODE ; 
 int VSYNC_POLARITY_CFG ; 
 scalar_t__ is_rockchip (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void analogix_dp_config_video_slave_mode(struct analogix_dp_device *dp)
{
	u32 reg;

	reg = readl(dp->reg_base + ANALOGIX_DP_FUNC_EN_1);
	if (dp->plat_data && is_rockchip(dp->plat_data->dev_type)) {
		reg &= ~(RK_VID_CAP_FUNC_EN_N | RK_VID_FIFO_FUNC_EN_N);
	} else {
		reg &= ~(MASTER_VID_FUNC_EN_N | SLAVE_VID_FUNC_EN_N);
		reg |= MASTER_VID_FUNC_EN_N;
	}
	writel(reg, dp->reg_base + ANALOGIX_DP_FUNC_EN_1);

	reg = readl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);
	reg &= ~INTERACE_SCAN_CFG;
	reg |= (dp->video_info.interlaced << 2);
	writel(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);

	reg = readl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);
	reg &= ~VSYNC_POLARITY_CFG;
	reg |= (dp->video_info.v_sync_polarity << 1);
	writel(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);

	reg = readl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);
	reg &= ~HSYNC_POLARITY_CFG;
	reg |= (dp->video_info.h_sync_polarity << 0);
	writel(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);

	reg = AUDIO_MODE_SPDIF_MODE | VIDEO_MODE_SLAVE_MODE;
	writel(reg, dp->reg_base + ANALOGIX_DP_SOC_GENERAL_CTL);
}