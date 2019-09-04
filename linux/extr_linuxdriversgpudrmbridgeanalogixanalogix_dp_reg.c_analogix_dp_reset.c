#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct analogix_dp_device {scalar_t__ reg_base; TYPE_1__* plat_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_type; } ;

/* Variables and functions */
 scalar_t__ ANALOGIX_DP_AUDIO_MARGIN ; 
 scalar_t__ ANALOGIX_DP_FUNC_EN_1 ; 
 scalar_t__ ANALOGIX_DP_FUNC_EN_2 ; 
 scalar_t__ ANALOGIX_DP_HDCP_CTL ; 
 scalar_t__ ANALOGIX_DP_HPD_DEGLITCH_H ; 
 scalar_t__ ANALOGIX_DP_HPD_DEGLITCH_L ; 
 scalar_t__ ANALOGIX_DP_LINK_DEBUG_CTL ; 
 scalar_t__ ANALOGIX_DP_M_AUD_GEN_FILTER_TH ; 
 scalar_t__ ANALOGIX_DP_M_VID_GEN_FILTER_TH ; 
 scalar_t__ ANALOGIX_DP_PHY_TEST ; 
 scalar_t__ ANALOGIX_DP_PKT_SEND_CTL ; 
 scalar_t__ ANALOGIX_DP_SOC_GENERAL_CTL ; 
 scalar_t__ ANALOGIX_DP_SYS_CTL_1 ; 
 scalar_t__ ANALOGIX_DP_SYS_CTL_2 ; 
 scalar_t__ ANALOGIX_DP_SYS_CTL_3 ; 
 scalar_t__ ANALOGIX_DP_SYS_CTL_4 ; 
 scalar_t__ ANALOGIX_DP_VIDEO_FIFO_THRD ; 
 int AUD_FIFO_FUNC_EN_N ; 
 int AUD_FUNC_EN_N ; 
 int AUX_FUNC_EN_N ; 
 int HDCP_FUNC_EN_N ; 
 int LS_CLK_DOMAIN_FUNC_EN_N ; 
 int MASTER_VID_FUNC_EN_N ; 
 int RK_VID_CAP_FUNC_EN_N ; 
 int RK_VID_FIFO_FUNC_EN_N ; 
 int SERDES_FIFO_FUNC_EN_N ; 
 int SLAVE_VID_FUNC_EN_N ; 
 int SSC_FUNC_EN_N ; 
 int SW_FUNC_EN_N ; 
 int /*<<< orphan*/  analogix_dp_enable_video_mute (struct analogix_dp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  analogix_dp_lane_swap (struct analogix_dp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  analogix_dp_stop_video (struct analogix_dp_device*) ; 
 scalar_t__ is_rockchip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void analogix_dp_reset(struct analogix_dp_device *dp)
{
	u32 reg;

	analogix_dp_stop_video(dp);
	analogix_dp_enable_video_mute(dp, 0);

	if (dp->plat_data && is_rockchip(dp->plat_data->dev_type))
		reg = RK_VID_CAP_FUNC_EN_N | RK_VID_FIFO_FUNC_EN_N |
			SW_FUNC_EN_N;
	else
		reg = MASTER_VID_FUNC_EN_N | SLAVE_VID_FUNC_EN_N |
			AUD_FIFO_FUNC_EN_N | AUD_FUNC_EN_N |
			HDCP_FUNC_EN_N | SW_FUNC_EN_N;

	writel(reg, dp->reg_base + ANALOGIX_DP_FUNC_EN_1);

	reg = SSC_FUNC_EN_N | AUX_FUNC_EN_N |
		SERDES_FIFO_FUNC_EN_N |
		LS_CLK_DOMAIN_FUNC_EN_N;
	writel(reg, dp->reg_base + ANALOGIX_DP_FUNC_EN_2);

	usleep_range(20, 30);

	analogix_dp_lane_swap(dp, 0);

	writel(0x0, dp->reg_base + ANALOGIX_DP_SYS_CTL_1);
	writel(0x40, dp->reg_base + ANALOGIX_DP_SYS_CTL_2);
	writel(0x0, dp->reg_base + ANALOGIX_DP_SYS_CTL_3);
	writel(0x0, dp->reg_base + ANALOGIX_DP_SYS_CTL_4);

	writel(0x0, dp->reg_base + ANALOGIX_DP_PKT_SEND_CTL);
	writel(0x0, dp->reg_base + ANALOGIX_DP_HDCP_CTL);

	writel(0x5e, dp->reg_base + ANALOGIX_DP_HPD_DEGLITCH_L);
	writel(0x1a, dp->reg_base + ANALOGIX_DP_HPD_DEGLITCH_H);

	writel(0x10, dp->reg_base + ANALOGIX_DP_LINK_DEBUG_CTL);

	writel(0x0, dp->reg_base + ANALOGIX_DP_PHY_TEST);

	writel(0x0, dp->reg_base + ANALOGIX_DP_VIDEO_FIFO_THRD);
	writel(0x20, dp->reg_base + ANALOGIX_DP_AUDIO_MARGIN);

	writel(0x4, dp->reg_base + ANALOGIX_DP_M_VID_GEN_FILTER_TH);
	writel(0x2, dp->reg_base + ANALOGIX_DP_M_AUD_GEN_FILTER_TH);

	writel(0x00000101, dp->reg_base + ANALOGIX_DP_SOC_GENERAL_CTL);
}