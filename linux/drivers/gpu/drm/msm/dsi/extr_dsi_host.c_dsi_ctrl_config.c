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
struct msm_dsi_phy_shared_timings {scalar_t__ clk_pre_inc_by_2; int /*<<< orphan*/  clk_pre; int /*<<< orphan*/  clk_post; } ;
struct msm_dsi_host {int mode_flags; int format; int lanes; int /*<<< orphan*/  dlane_swap; int /*<<< orphan*/  channel; struct msm_dsi_cfg_handler* cfg_hnd; } ;
struct msm_dsi_cfg_handler {scalar_t__ major; scalar_t__ minor; } ;
typedef  enum mipi_dsi_pixel_format { ____Placeholder_mipi_dsi_pixel_format } mipi_dsi_pixel_format ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int DSI_CLKOUT_TIMING_CTRL_T_CLK_POST (int /*<<< orphan*/ ) ; 
 int DSI_CLKOUT_TIMING_CTRL_T_CLK_PRE (int /*<<< orphan*/ ) ; 
 int DSI_CLK_CTRL_ENABLE_CLKS ; 
 int DSI_CMD_CFG0_DST_FORMAT (int /*<<< orphan*/ ) ; 
 int DSI_CMD_CFG0_RGB_SWAP (int /*<<< orphan*/ ) ; 
 int DSI_CMD_CFG1_INSERT_DCS_COMMAND ; 
 int DSI_CMD_CFG1_WR_MEM_CONTINUE (int /*<<< orphan*/ ) ; 
 int DSI_CMD_CFG1_WR_MEM_START (int /*<<< orphan*/ ) ; 
 int DSI_CMD_DMA_CTRL_FROM_FRAME_BUFFER ; 
 int DSI_CMD_DMA_CTRL_LOW_POWER ; 
 int DSI_CTRL_CLK_EN ; 
 int DSI_CTRL_ENABLE ; 
 int DSI_CTRL_LANE0 ; 
 int DSI_EOT_PACKET_CTRL_TX_EOT_APPEND ; 
 int /*<<< orphan*/  DSI_IRQ_MASK_ERROR ; 
 int DSI_LANE_CTRL_CLKLN_HS_FORCE_REQUEST ; 
 int DSI_LANE_SWAP_CTRL_DLN_SWAP_SEL (int /*<<< orphan*/ ) ; 
 int DSI_TRIG_CTRL_BLOCK_DMA_WITHIN_FRAME ; 
 int DSI_TRIG_CTRL_DMA_TRIGGER (int /*<<< orphan*/ ) ; 
 int DSI_TRIG_CTRL_MDP_TRIGGER (int /*<<< orphan*/ ) ; 
 int DSI_TRIG_CTRL_STREAM (int /*<<< orphan*/ ) ; 
 int DSI_TRIG_CTRL_TE ; 
 int DSI_T_CLK_PRE_EXTEND_INC_BY_2_BYTECLK ; 
 int DSI_VID_CFG0_BLLP_POWER_STOP ; 
 int DSI_VID_CFG0_DST_FORMAT (int /*<<< orphan*/ ) ; 
 int DSI_VID_CFG0_EOF_BLLP_POWER_STOP ; 
 int DSI_VID_CFG0_HBP_POWER_STOP ; 
 int DSI_VID_CFG0_HFP_POWER_STOP ; 
 int DSI_VID_CFG0_HSA_POWER_STOP ; 
 int DSI_VID_CFG0_PULSE_MODE_HSA_HE ; 
 int DSI_VID_CFG0_TRAFFIC_MODE (int /*<<< orphan*/ ) ; 
 int DSI_VID_CFG0_VIRT_CHANNEL (int /*<<< orphan*/ ) ; 
 int DSI_VID_CFG1_RGB_SWAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIPI_DCS_WRITE_MEMORY_CONTINUE ; 
 int /*<<< orphan*/  MIPI_DCS_WRITE_MEMORY_START ; 
 int MIPI_DSI_CLOCK_NON_CONTINUOUS ; 
 int MIPI_DSI_MODE_EOT_PACKET ; 
 int MIPI_DSI_MODE_VIDEO ; 
 int MIPI_DSI_MODE_VIDEO_HBP ; 
 int MIPI_DSI_MODE_VIDEO_HFP ; 
 int MIPI_DSI_MODE_VIDEO_HSA ; 
 int MIPI_DSI_MODE_VIDEO_HSE ; 
 scalar_t__ MSM_DSI_6G_VER_MINOR_V1_0 ; 
 scalar_t__ MSM_DSI_6G_VER_MINOR_V1_2 ; 
 scalar_t__ MSM_DSI_VER_MAJOR_6G ; 
 int /*<<< orphan*/  REG_DSI_CLKOUT_TIMING_CTRL ; 
 int /*<<< orphan*/  REG_DSI_CLK_CTRL ; 
 int /*<<< orphan*/  REG_DSI_CMD_CFG0 ; 
 int /*<<< orphan*/  REG_DSI_CMD_CFG1 ; 
 int /*<<< orphan*/  REG_DSI_CMD_DMA_CTRL ; 
 int /*<<< orphan*/  REG_DSI_CTRL ; 
 int /*<<< orphan*/  REG_DSI_EOT_PACKET_CTRL ; 
 int /*<<< orphan*/  REG_DSI_ERR_INT_MASK0 ; 
 int /*<<< orphan*/  REG_DSI_LANE_CTRL ; 
 int /*<<< orphan*/  REG_DSI_LANE_SWAP_CTRL ; 
 int /*<<< orphan*/  REG_DSI_TRIG_CTRL ; 
 int /*<<< orphan*/  REG_DSI_T_CLK_PRE_EXTEND ; 
 int /*<<< orphan*/  REG_DSI_VID_CFG0 ; 
 int /*<<< orphan*/  REG_DSI_VID_CFG1 ; 
 int /*<<< orphan*/  SWAP_RGB ; 
 int /*<<< orphan*/  TRIGGER_NONE ; 
 int /*<<< orphan*/  TRIGGER_SW ; 
 int /*<<< orphan*/  dsi_get_cmd_fmt (int) ; 
 int /*<<< orphan*/  dsi_get_traffic_mode (int) ; 
 int /*<<< orphan*/  dsi_get_vid_fmt (int) ; 
 int /*<<< orphan*/  dsi_intr_ctrl (struct msm_dsi_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsi_write (struct msm_dsi_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dsi_ctrl_config(struct msm_dsi_host *msm_host, bool enable,
			struct msm_dsi_phy_shared_timings *phy_shared_timings)
{
	u32 flags = msm_host->mode_flags;
	enum mipi_dsi_pixel_format mipi_fmt = msm_host->format;
	const struct msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;
	u32 data = 0;

	if (!enable) {
		dsi_write(msm_host, REG_DSI_CTRL, 0);
		return;
	}

	if (flags & MIPI_DSI_MODE_VIDEO) {
		if (flags & MIPI_DSI_MODE_VIDEO_HSE)
			data |= DSI_VID_CFG0_PULSE_MODE_HSA_HE;
		if (flags & MIPI_DSI_MODE_VIDEO_HFP)
			data |= DSI_VID_CFG0_HFP_POWER_STOP;
		if (flags & MIPI_DSI_MODE_VIDEO_HBP)
			data |= DSI_VID_CFG0_HBP_POWER_STOP;
		if (flags & MIPI_DSI_MODE_VIDEO_HSA)
			data |= DSI_VID_CFG0_HSA_POWER_STOP;
		/* Always set low power stop mode for BLLP
		 * to let command engine send packets
		 */
		data |= DSI_VID_CFG0_EOF_BLLP_POWER_STOP |
			DSI_VID_CFG0_BLLP_POWER_STOP;
		data |= DSI_VID_CFG0_TRAFFIC_MODE(dsi_get_traffic_mode(flags));
		data |= DSI_VID_CFG0_DST_FORMAT(dsi_get_vid_fmt(mipi_fmt));
		data |= DSI_VID_CFG0_VIRT_CHANNEL(msm_host->channel);
		dsi_write(msm_host, REG_DSI_VID_CFG0, data);

		/* Do not swap RGB colors */
		data = DSI_VID_CFG1_RGB_SWAP(SWAP_RGB);
		dsi_write(msm_host, REG_DSI_VID_CFG1, 0);
	} else {
		/* Do not swap RGB colors */
		data = DSI_CMD_CFG0_RGB_SWAP(SWAP_RGB);
		data |= DSI_CMD_CFG0_DST_FORMAT(dsi_get_cmd_fmt(mipi_fmt));
		dsi_write(msm_host, REG_DSI_CMD_CFG0, data);

		data = DSI_CMD_CFG1_WR_MEM_START(MIPI_DCS_WRITE_MEMORY_START) |
			DSI_CMD_CFG1_WR_MEM_CONTINUE(
					MIPI_DCS_WRITE_MEMORY_CONTINUE);
		/* Always insert DCS command */
		data |= DSI_CMD_CFG1_INSERT_DCS_COMMAND;
		dsi_write(msm_host, REG_DSI_CMD_CFG1, data);
	}

	dsi_write(msm_host, REG_DSI_CMD_DMA_CTRL,
			DSI_CMD_DMA_CTRL_FROM_FRAME_BUFFER |
			DSI_CMD_DMA_CTRL_LOW_POWER);

	data = 0;
	/* Always assume dedicated TE pin */
	data |= DSI_TRIG_CTRL_TE;
	data |= DSI_TRIG_CTRL_MDP_TRIGGER(TRIGGER_NONE);
	data |= DSI_TRIG_CTRL_DMA_TRIGGER(TRIGGER_SW);
	data |= DSI_TRIG_CTRL_STREAM(msm_host->channel);
	if ((cfg_hnd->major == MSM_DSI_VER_MAJOR_6G) &&
		(cfg_hnd->minor >= MSM_DSI_6G_VER_MINOR_V1_2))
		data |= DSI_TRIG_CTRL_BLOCK_DMA_WITHIN_FRAME;
	dsi_write(msm_host, REG_DSI_TRIG_CTRL, data);

	data = DSI_CLKOUT_TIMING_CTRL_T_CLK_POST(phy_shared_timings->clk_post) |
		DSI_CLKOUT_TIMING_CTRL_T_CLK_PRE(phy_shared_timings->clk_pre);
	dsi_write(msm_host, REG_DSI_CLKOUT_TIMING_CTRL, data);

	if ((cfg_hnd->major == MSM_DSI_VER_MAJOR_6G) &&
	    (cfg_hnd->minor > MSM_DSI_6G_VER_MINOR_V1_0) &&
	    phy_shared_timings->clk_pre_inc_by_2)
		dsi_write(msm_host, REG_DSI_T_CLK_PRE_EXTEND,
			  DSI_T_CLK_PRE_EXTEND_INC_BY_2_BYTECLK);

	data = 0;
	if (!(flags & MIPI_DSI_MODE_EOT_PACKET))
		data |= DSI_EOT_PACKET_CTRL_TX_EOT_APPEND;
	dsi_write(msm_host, REG_DSI_EOT_PACKET_CTRL, data);

	/* allow only ack-err-status to generate interrupt */
	dsi_write(msm_host, REG_DSI_ERR_INT_MASK0, 0x13ff3fe0);

	dsi_intr_ctrl(msm_host, DSI_IRQ_MASK_ERROR, 1);

	dsi_write(msm_host, REG_DSI_CLK_CTRL, DSI_CLK_CTRL_ENABLE_CLKS);

	data = DSI_CTRL_CLK_EN;

	DBG("lane number=%d", msm_host->lanes);
	data |= ((DSI_CTRL_LANE0 << msm_host->lanes) - DSI_CTRL_LANE0);

	dsi_write(msm_host, REG_DSI_LANE_SWAP_CTRL,
		  DSI_LANE_SWAP_CTRL_DLN_SWAP_SEL(msm_host->dlane_swap));

	if (!(flags & MIPI_DSI_CLOCK_NON_CONTINUOUS))
		dsi_write(msm_host, REG_DSI_LANE_CTRL,
			DSI_LANE_CTRL_CLKLN_HS_FORCE_REQUEST);

	data |= DSI_CTRL_ENABLE;

	dsi_write(msm_host, REG_DSI_CTRL, data);
}