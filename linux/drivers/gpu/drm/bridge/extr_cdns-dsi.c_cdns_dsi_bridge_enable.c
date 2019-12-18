#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  unsigned long u32 ;
struct phy_configure_opts_mipi_dphy {unsigned long hs_prepare; unsigned long hs_zero; int /*<<< orphan*/  hs_clk_rate; } ;
struct drm_display_mode {unsigned long crtc_vdisplay; scalar_t__ crtc_vsync_start; scalar_t__ crtc_vsync_end; scalar_t__ crtc_vtotal; } ;
struct drm_bridge {TYPE_4__* encoder; } ;
struct TYPE_7__ {struct phy_configure_opts_mipi_dphy mipi_dphy; } ;
struct cdns_dsi_output {TYPE_6__* dev; TYPE_1__ phy_opts; } ;
struct cdns_dsi_input {int /*<<< orphan*/  id; } ;
struct cdns_dsi_cfg {unsigned long hsa; unsigned long htotal; int /*<<< orphan*/  hact; int /*<<< orphan*/  hfp; int /*<<< orphan*/  hbp; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct cdns_dsi {scalar_t__ regs; TYPE_5__ base; struct cdns_dsi_output output; } ;
struct TYPE_12__ {int format; int lanes; int mode_flags; } ;
struct TYPE_10__ {TYPE_3__* crtc; } ;
struct TYPE_9__ {TYPE_2__* state; } ;
struct TYPE_8__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 unsigned long BLK_LINE_EVENT_PKT_LEN (unsigned long) ; 
 unsigned long BLK_LINE_PULSE_PKT_LEN (unsigned long) ; 
 unsigned long CLK_DIV (unsigned long) ; 
 unsigned long CLK_DIV_MAX ; 
 unsigned long DIV_ROUND_DOWN_ULL (int,int /*<<< orphan*/ ) ; 
 unsigned long DIV_ROUND_UP (unsigned long,int) ; 
 unsigned long DSI_BLANKING_FRAME_OVERHEAD ; 
 unsigned long DSI_EOT_PKT_SIZE ; 
 unsigned long DSI_HSA_FRAME_OVERHEAD ; 
 unsigned long DSI_HSS_VSS_VSE_FRAME_OVERHEAD ; 
 scalar_t__ DSI_NULL_FRAME_OVERHEAD ; 
 unsigned long HACT_LEN (int /*<<< orphan*/ ) ; 
 unsigned long HBP_LEN (int /*<<< orphan*/ ) ; 
 unsigned long HFP_LEN (int /*<<< orphan*/ ) ; 
 unsigned long HOST_EOT_GEN ; 
 unsigned long HSA_LEN (unsigned long) ; 
 unsigned long HSTX_TIMEOUT (unsigned long) ; 
 unsigned long HSTX_TIMEOUT_MAX ; 
 unsigned long IF_EN (int /*<<< orphan*/ ) ; 
 unsigned long IF_VID_MODE ; 
 unsigned long IF_VID_SELECT (int /*<<< orphan*/ ) ; 
 unsigned long IF_VID_SELECT_MASK ; 
 unsigned long LPRX_TIMEOUT (unsigned long) ; 
 unsigned long MAX_LINE_LIMIT (scalar_t__) ; 
 scalar_t__ MCTL_DPHY_TIMEOUT1 ; 
 scalar_t__ MCTL_DPHY_TIMEOUT2 ; 
 scalar_t__ MCTL_MAIN_DATA_CTL ; 
 scalar_t__ MCTL_MAIN_EN ; 
#define  MIPI_DSI_FMT_RGB565 131 
#define  MIPI_DSI_FMT_RGB666 130 
#define  MIPI_DSI_FMT_RGB666_PACKED 129 
#define  MIPI_DSI_FMT_RGB888 128 
 int MIPI_DSI_MODE_EOT_PACKET ; 
 int MIPI_DSI_MODE_VIDEO ; 
 int MIPI_DSI_MODE_VIDEO_SYNC_PULSE ; 
 int /*<<< orphan*/  MIPI_DSI_PACKED_PIXEL_STREAM_16 ; 
 int /*<<< orphan*/  MIPI_DSI_PACKED_PIXEL_STREAM_18 ; 
 int /*<<< orphan*/  MIPI_DSI_PACKED_PIXEL_STREAM_24 ; 
 int /*<<< orphan*/  MIPI_DSI_PIXEL_STREAM_3BYTE_18 ; 
 unsigned long NSEC_PER_SEC ; 
 unsigned long RECOVERY_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECOVERY_MODE_NEXT_HSYNC ; 
 unsigned long REG_BLKEOL_MODE (int /*<<< orphan*/ ) ; 
 unsigned long REG_BLKLINE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_BLK_MODE_BLANKING_PKT ; 
 unsigned long REG_LINE_DURATION (unsigned long) ; 
 unsigned long REG_WAKEUP_TIME (unsigned long) ; 
 unsigned long SYNC_PULSE_ACTIVE ; 
 unsigned long SYNC_PULSE_HORIZONTAL ; 
 unsigned long VBP_LEN (scalar_t__) ; 
 unsigned long VFP_LEN (scalar_t__) ; 
 scalar_t__ VID_BLKSIZE1 ; 
 scalar_t__ VID_BLKSIZE2 ; 
 unsigned long VID_DATATYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VID_DPHY_TIME ; 
 unsigned long VID_EN ; 
 scalar_t__ VID_HSIZE1 ; 
 scalar_t__ VID_HSIZE2 ; 
 unsigned long VID_IGNORE_MISS_VSYNC ; 
 scalar_t__ VID_MAIN_CTL ; 
 unsigned long VID_PIXEL_MODE_RGB565 ; 
 unsigned long VID_PIXEL_MODE_RGB666 ; 
 unsigned long VID_PIXEL_MODE_RGB666_PACKED ; 
 unsigned long VID_PIXEL_MODE_RGB888 ; 
 scalar_t__ VID_VCA_SETTING2 ; 
 scalar_t__ VID_VSIZE1 ; 
 scalar_t__ VID_VSIZE2 ; 
 unsigned long VSA_LEN (scalar_t__) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 struct cdns_dsi_input* bridge_to_cdns_dsi_input (struct drm_bridge*) ; 
 int /*<<< orphan*/  cdns_dsi_check_conf (struct cdns_dsi*,struct drm_display_mode*,struct cdns_dsi_cfg*,int) ; 
 int /*<<< orphan*/  cdns_dsi_hs_init (struct cdns_dsi*) ; 
 int /*<<< orphan*/  cdns_dsi_init_link (struct cdns_dsi*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long drm_mode_vrefresh (struct drm_display_mode*) ; 
 struct cdns_dsi* input_to_dsi (struct cdns_dsi_input*) ; 
 int mipi_dsi_pixel_format_to_bpp (int) ; 
 scalar_t__ pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void cdns_dsi_bridge_enable(struct drm_bridge *bridge)
{
	struct cdns_dsi_input *input = bridge_to_cdns_dsi_input(bridge);
	struct cdns_dsi *dsi = input_to_dsi(input);
	struct cdns_dsi_output *output = &dsi->output;
	struct drm_display_mode *mode;
	struct phy_configure_opts_mipi_dphy *phy_cfg = &output->phy_opts.mipi_dphy;
	unsigned long tx_byte_period;
	struct cdns_dsi_cfg dsi_cfg;
	u32 tmp, reg_wakeup, div;
	int bpp, nlanes;

	if (WARN_ON(pm_runtime_get_sync(dsi->base.dev) < 0))
		return;

	mode = &bridge->encoder->crtc->state->adjusted_mode;
	bpp = mipi_dsi_pixel_format_to_bpp(output->dev->format);
	nlanes = output->dev->lanes;

	WARN_ON_ONCE(cdns_dsi_check_conf(dsi, mode, &dsi_cfg, false));

	cdns_dsi_hs_init(dsi);
	cdns_dsi_init_link(dsi);

	writel(HBP_LEN(dsi_cfg.hbp) | HSA_LEN(dsi_cfg.hsa),
	       dsi->regs + VID_HSIZE1);
	writel(HFP_LEN(dsi_cfg.hfp) | HACT_LEN(dsi_cfg.hact),
	       dsi->regs + VID_HSIZE2);

	writel(VBP_LEN(mode->crtc_vtotal - mode->crtc_vsync_end - 1) |
	       VFP_LEN(mode->crtc_vsync_start - mode->crtc_vdisplay) |
	       VSA_LEN(mode->crtc_vsync_end - mode->crtc_vsync_start + 1),
	       dsi->regs + VID_VSIZE1);
	writel(mode->crtc_vdisplay, dsi->regs + VID_VSIZE2);

	tmp = dsi_cfg.htotal -
	      (dsi_cfg.hsa + DSI_BLANKING_FRAME_OVERHEAD +
	       DSI_HSA_FRAME_OVERHEAD);
	writel(BLK_LINE_PULSE_PKT_LEN(tmp), dsi->regs + VID_BLKSIZE2);
	if (output->dev->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
		writel(MAX_LINE_LIMIT(tmp - DSI_NULL_FRAME_OVERHEAD),
		       dsi->regs + VID_VCA_SETTING2);

	tmp = dsi_cfg.htotal -
	      (DSI_HSS_VSS_VSE_FRAME_OVERHEAD + DSI_BLANKING_FRAME_OVERHEAD);
	writel(BLK_LINE_EVENT_PKT_LEN(tmp), dsi->regs + VID_BLKSIZE1);
	if (!(output->dev->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE))
		writel(MAX_LINE_LIMIT(tmp - DSI_NULL_FRAME_OVERHEAD),
		       dsi->regs + VID_VCA_SETTING2);

	tmp = DIV_ROUND_UP(dsi_cfg.htotal, nlanes) -
	      DIV_ROUND_UP(dsi_cfg.hsa, nlanes);

	if (!(output->dev->mode_flags & MIPI_DSI_MODE_EOT_PACKET))
		tmp -= DIV_ROUND_UP(DSI_EOT_PKT_SIZE, nlanes);

	tx_byte_period = DIV_ROUND_DOWN_ULL((u64)NSEC_PER_SEC * 8,
					    phy_cfg->hs_clk_rate);
	reg_wakeup = (phy_cfg->hs_prepare + phy_cfg->hs_zero) / tx_byte_period;
	writel(REG_WAKEUP_TIME(reg_wakeup) | REG_LINE_DURATION(tmp),
	       dsi->regs + VID_DPHY_TIME);

	/*
	 * HSTX and LPRX timeouts are both expressed in TX byte clk cycles and
	 * both should be set to at least the time it takes to transmit a
	 * frame.
	 */
	tmp = NSEC_PER_SEC / drm_mode_vrefresh(mode);
	tmp /= tx_byte_period;

	for (div = 0; div <= CLK_DIV_MAX; div++) {
		if (tmp <= HSTX_TIMEOUT_MAX)
			break;

		tmp >>= 1;
	}

	if (tmp > HSTX_TIMEOUT_MAX)
		tmp = HSTX_TIMEOUT_MAX;

	writel(CLK_DIV(div) | HSTX_TIMEOUT(tmp),
	       dsi->regs + MCTL_DPHY_TIMEOUT1);

	writel(LPRX_TIMEOUT(tmp), dsi->regs + MCTL_DPHY_TIMEOUT2);

	if (output->dev->mode_flags & MIPI_DSI_MODE_VIDEO) {
		switch (output->dev->format) {
		case MIPI_DSI_FMT_RGB888:
			tmp = VID_PIXEL_MODE_RGB888 |
			      VID_DATATYPE(MIPI_DSI_PACKED_PIXEL_STREAM_24);
			break;

		case MIPI_DSI_FMT_RGB666:
			tmp = VID_PIXEL_MODE_RGB666 |
			      VID_DATATYPE(MIPI_DSI_PIXEL_STREAM_3BYTE_18);
			break;

		case MIPI_DSI_FMT_RGB666_PACKED:
			tmp = VID_PIXEL_MODE_RGB666_PACKED |
			      VID_DATATYPE(MIPI_DSI_PACKED_PIXEL_STREAM_18);
			break;

		case MIPI_DSI_FMT_RGB565:
			tmp = VID_PIXEL_MODE_RGB565 |
			      VID_DATATYPE(MIPI_DSI_PACKED_PIXEL_STREAM_16);
			break;

		default:
			dev_err(dsi->base.dev, "Unsupported DSI format\n");
			return;
		}

		if (output->dev->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
			tmp |= SYNC_PULSE_ACTIVE | SYNC_PULSE_HORIZONTAL;

		tmp |= REG_BLKLINE_MODE(REG_BLK_MODE_BLANKING_PKT) |
		       REG_BLKEOL_MODE(REG_BLK_MODE_BLANKING_PKT) |
		       RECOVERY_MODE(RECOVERY_MODE_NEXT_HSYNC) |
		       VID_IGNORE_MISS_VSYNC;

		writel(tmp, dsi->regs + VID_MAIN_CTL);
	}

	tmp = readl(dsi->regs + MCTL_MAIN_DATA_CTL);
	tmp &= ~(IF_VID_SELECT_MASK | HOST_EOT_GEN | IF_VID_MODE);

	if (!(output->dev->mode_flags & MIPI_DSI_MODE_EOT_PACKET))
		tmp |= HOST_EOT_GEN;

	if (output->dev->mode_flags & MIPI_DSI_MODE_VIDEO)
		tmp |= IF_VID_MODE | IF_VID_SELECT(input->id) | VID_EN;

	writel(tmp, dsi->regs + MCTL_MAIN_DATA_CTL);

	tmp = readl(dsi->regs + MCTL_MAIN_EN) | IF_EN(input->id);
	writel(tmp, dsi->regs + MCTL_MAIN_EN);
}