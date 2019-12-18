#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vc4_dsi_encoder {struct vc4_dsi* dsi; } ;
struct vc4_dsi {int port; unsigned long divider; int lanes; int mode_flags; int format; int /*<<< orphan*/  regset; TYPE_3__* pdev; int /*<<< orphan*/  bridge; int /*<<< orphan*/  pixel_clock; int /*<<< orphan*/  pll_phy_clock; int /*<<< orphan*/  escape_clock; } ;
struct drm_printer {int dummy; } ;
struct drm_encoder {TYPE_2__* crtc; } ;
struct drm_display_mode {int clock; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device dev; } ;
struct TYPE_5__ {TYPE_1__* state; } ;
struct TYPE_4__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_RESET_FIFOS ; 
 int /*<<< orphan*/  DISP0_CTRL ; 
 int /*<<< orphan*/  DISP1_CTRL ; 
 int DIV_ROUND_UP (int,unsigned long) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int DSI0_CTRL_CTRL0 ; 
 int /*<<< orphan*/  DSI0_PHYC_ESC_CLK_LPDT ; 
 int DSI0_PHY_AFEC0_PD_DLANE1 ; 
 int DSI0_PHY_AFEC0_RESET ; 
 int /*<<< orphan*/  DSI0_PHY_AFEC1_IDR_CLANE ; 
 int /*<<< orphan*/  DSI0_PHY_AFEC1_IDR_DLANE0 ; 
 int /*<<< orphan*/  DSI0_PHY_AFEC1_IDR_DLANE1 ; 
 int DSI1_CTRL_EN ; 
 int /*<<< orphan*/  DSI1_PHYC_ESC_CLK_LPDT ; 
 int /*<<< orphan*/  DSI1_PHY_AFEC0_IDR_CLANE ; 
 int /*<<< orphan*/  DSI1_PHY_AFEC0_IDR_DLANE0 ; 
 int /*<<< orphan*/  DSI1_PHY_AFEC0_IDR_DLANE1 ; 
 int /*<<< orphan*/  DSI1_PHY_AFEC0_IDR_DLANE2 ; 
 int /*<<< orphan*/  DSI1_PHY_AFEC0_IDR_DLANE3 ; 
 int DSI1_PHY_AFEC0_PD_DLANE1 ; 
 int DSI1_PHY_AFEC0_PD_DLANE2 ; 
 int DSI1_PHY_AFEC0_PD_DLANE3 ; 
 int DSI1_PHY_AFEC0_RESET ; 
 int DSI_CTRL_CAL_BYTE ; 
 int DSI_CTRL_HSDT_EOT_DISABLE ; 
 int DSI_CTRL_RX_LPDT_EOT_DISABLE ; 
 int DSI_CTRL_SOFT_RESET_CFG ; 
 int DSI_DISP0_COMMAND_MODE ; 
 int DSI_DISP0_ENABLE ; 
 int /*<<< orphan*/  DSI_DISP0_LP_STOP_CTRL ; 
 int DSI_DISP0_LP_STOP_PERFRAME ; 
 int /*<<< orphan*/  DSI_DISP0_PFORMAT ; 
 int /*<<< orphan*/  DSI_DISP0_PIX_CLK_DIV ; 
 int DSI_DISP0_ST_END ; 
 int DSI_DISP1_ENABLE ; 
 int /*<<< orphan*/  DSI_DISP1_PFORMAT ; 
 int DSI_DISP1_PFORMAT_32BIT_LE ; 
 int /*<<< orphan*/  DSI_HS_CLT0_CPRE ; 
 int /*<<< orphan*/  DSI_HS_CLT0_CPREP ; 
 int /*<<< orphan*/  DSI_HS_CLT0_CZERO ; 
 int /*<<< orphan*/  DSI_HS_CLT1_CPOST ; 
 int /*<<< orphan*/  DSI_HS_CLT1_CTRAIL ; 
 int /*<<< orphan*/  DSI_HS_CLT2_WUP ; 
 int /*<<< orphan*/  DSI_HS_DLT3_EXIT ; 
 int /*<<< orphan*/  DSI_HS_DLT3_PRE ; 
 int /*<<< orphan*/  DSI_HS_DLT3_ZERO ; 
 int /*<<< orphan*/  DSI_HS_DLT4_ANLAT ; 
 int /*<<< orphan*/  DSI_HS_DLT4_LPX ; 
 int /*<<< orphan*/  DSI_HS_DLT4_TRAIL ; 
 int /*<<< orphan*/  DSI_HS_DLT5_INIT ; 
 int /*<<< orphan*/  DSI_HS_DLT6_LP_LPX ; 
 int /*<<< orphan*/  DSI_HS_DLT6_TA_GET ; 
 int /*<<< orphan*/  DSI_HS_DLT6_TA_GO ; 
 int /*<<< orphan*/  DSI_HS_DLT6_TA_SURE ; 
 int /*<<< orphan*/  DSI_HS_DLT7_LP_WUP ; 
 int DSI_PHYC_DLANE0_ENABLE ; 
 int DSI_PHYC_DLANE1_ENABLE ; 
 int DSI_PHYC_DLANE2_ENABLE ; 
 int DSI_PHYC_DLANE3_ENABLE ; 
 int /*<<< orphan*/  DSI_PHY_AFEC0_CTATADJ ; 
 int /*<<< orphan*/  DSI_PHY_AFEC0_PTATADJ ; 
 int DSI_PORT_BIT (int /*<<< orphan*/ ) ; 
 int DSI_PORT_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSI_PORT_WRITE (int /*<<< orphan*/ ,int) ; 
 int ESC_TIME_NS ; 
 int /*<<< orphan*/  HSTX_TO_CNT ; 
 int /*<<< orphan*/  HS_CLT0 ; 
 int /*<<< orphan*/  HS_CLT1 ; 
 int /*<<< orphan*/  HS_CLT2 ; 
 int /*<<< orphan*/  HS_DLT3 ; 
 int /*<<< orphan*/  HS_DLT4 ; 
 int /*<<< orphan*/  HS_DLT5 ; 
 int /*<<< orphan*/  HS_DLT6 ; 
 int /*<<< orphan*/  HS_DLT7 ; 
 int /*<<< orphan*/  LPRX_TO_CNT ; 
 int MIPI_DSI_CLOCK_NON_CONTINUOUS ; 
 int MIPI_DSI_MODE_VIDEO ; 
 int /*<<< orphan*/  PHYC ; 
 int /*<<< orphan*/  PHYC_CLANE_ENABLE ; 
 int /*<<< orphan*/  PHYC_HS_CLK_CONTINUOUS ; 
 int /*<<< orphan*/  PHY_AFEC0 ; 
 int /*<<< orphan*/  PHY_AFEC1 ; 
 int /*<<< orphan*/  PR_TO_CNT ; 
 int /*<<< orphan*/  STAT ; 
 int /*<<< orphan*/  TA_TO_CNT ; 
 int VC4_SET_FIELD (int,int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned long,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  drm_bridge_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_bridge_pre_enable (int /*<<< orphan*/ ) ; 
 struct drm_printer drm_info_printer (struct device*) ; 
 int /*<<< orphan*/  drm_print_regset32 (struct drm_printer*,int /*<<< orphan*/ *) ; 
 int dsi_esc_timing (int) ; 
 int dsi_hs_timing (int,int,int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int pm_runtime_get_sync (struct device*) ; 
 struct vc4_dsi_encoder* to_vc4_dsi_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  vc4_dsi_ulps (struct vc4_dsi*,int) ; 

__attribute__((used)) static void vc4_dsi_encoder_enable(struct drm_encoder *encoder)
{
	struct drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	struct vc4_dsi_encoder *vc4_encoder = to_vc4_dsi_encoder(encoder);
	struct vc4_dsi *dsi = vc4_encoder->dsi;
	struct device *dev = &dsi->pdev->dev;
	bool debug_dump_regs = false;
	unsigned long hs_clock;
	u32 ui_ns;
	/* Minimum LP state duration in escape clock cycles. */
	u32 lpx = dsi_esc_timing(60);
	unsigned long pixel_clock_hz = mode->clock * 1000;
	unsigned long dsip_clock;
	unsigned long phy_clock;
	int ret;

	ret = pm_runtime_get_sync(dev);
	if (ret) {
		DRM_ERROR("Failed to runtime PM enable on DSI%d\n", dsi->port);
		return;
	}

	if (debug_dump_regs) {
		struct drm_printer p = drm_info_printer(&dsi->pdev->dev);
		dev_info(&dsi->pdev->dev, "DSI regs before:\n");
		drm_print_regset32(&p, &dsi->regset);
	}

	/* Round up the clk_set_rate() request slightly, since
	 * PLLD_DSI1 is an integer divider and its rate selection will
	 * never round up.
	 */
	phy_clock = (pixel_clock_hz + 1000) * dsi->divider;
	ret = clk_set_rate(dsi->pll_phy_clock, phy_clock);
	if (ret) {
		dev_err(&dsi->pdev->dev,
			"Failed to set phy clock to %ld: %d\n", phy_clock, ret);
	}

	/* Reset the DSI and all its fifos. */
	DSI_PORT_WRITE(CTRL,
		       DSI_CTRL_SOFT_RESET_CFG |
		       DSI_PORT_BIT(CTRL_RESET_FIFOS));

	DSI_PORT_WRITE(CTRL,
		       DSI_CTRL_HSDT_EOT_DISABLE |
		       DSI_CTRL_RX_LPDT_EOT_DISABLE);

	/* Clear all stat bits so we see what has happened during enable. */
	DSI_PORT_WRITE(STAT, DSI_PORT_READ(STAT));

	/* Set AFE CTR00/CTR1 to release powerdown of analog. */
	if (dsi->port == 0) {
		u32 afec0 = (VC4_SET_FIELD(7, DSI_PHY_AFEC0_PTATADJ) |
			     VC4_SET_FIELD(7, DSI_PHY_AFEC0_CTATADJ));

		if (dsi->lanes < 2)
			afec0 |= DSI0_PHY_AFEC0_PD_DLANE1;

		if (!(dsi->mode_flags & MIPI_DSI_MODE_VIDEO))
			afec0 |= DSI0_PHY_AFEC0_RESET;

		DSI_PORT_WRITE(PHY_AFEC0, afec0);

		DSI_PORT_WRITE(PHY_AFEC1,
			       VC4_SET_FIELD(6,  DSI0_PHY_AFEC1_IDR_DLANE1) |
			       VC4_SET_FIELD(6,  DSI0_PHY_AFEC1_IDR_DLANE0) |
			       VC4_SET_FIELD(6,  DSI0_PHY_AFEC1_IDR_CLANE));
	} else {
		u32 afec0 = (VC4_SET_FIELD(7, DSI_PHY_AFEC0_PTATADJ) |
			     VC4_SET_FIELD(7, DSI_PHY_AFEC0_CTATADJ) |
			     VC4_SET_FIELD(6, DSI1_PHY_AFEC0_IDR_CLANE) |
			     VC4_SET_FIELD(6, DSI1_PHY_AFEC0_IDR_DLANE0) |
			     VC4_SET_FIELD(6, DSI1_PHY_AFEC0_IDR_DLANE1) |
			     VC4_SET_FIELD(6, DSI1_PHY_AFEC0_IDR_DLANE2) |
			     VC4_SET_FIELD(6, DSI1_PHY_AFEC0_IDR_DLANE3));

		if (dsi->lanes < 4)
			afec0 |= DSI1_PHY_AFEC0_PD_DLANE3;
		if (dsi->lanes < 3)
			afec0 |= DSI1_PHY_AFEC0_PD_DLANE2;
		if (dsi->lanes < 2)
			afec0 |= DSI1_PHY_AFEC0_PD_DLANE1;

		afec0 |= DSI1_PHY_AFEC0_RESET;

		DSI_PORT_WRITE(PHY_AFEC0, afec0);

		DSI_PORT_WRITE(PHY_AFEC1, 0);

		/* AFEC reset hold time */
		mdelay(1);
	}

	ret = clk_prepare_enable(dsi->escape_clock);
	if (ret) {
		DRM_ERROR("Failed to turn on DSI escape clock: %d\n", ret);
		return;
	}

	ret = clk_prepare_enable(dsi->pll_phy_clock);
	if (ret) {
		DRM_ERROR("Failed to turn on DSI PLL: %d\n", ret);
		return;
	}

	hs_clock = clk_get_rate(dsi->pll_phy_clock);

	/* Yes, we set the DSI0P/DSI1P pixel clock to the byte rate,
	 * not the pixel clock rate.  DSIxP take from the APHY's byte,
	 * DDR2, or DDR4 clock (we use byte) and feed into the PV at
	 * that rate.  Separately, a value derived from PIX_CLK_DIV
	 * and HS_CLKC is fed into the PV to divide down to the actual
	 * pixel clock for pushing pixels into DSI.
	 */
	dsip_clock = phy_clock / 8;
	ret = clk_set_rate(dsi->pixel_clock, dsip_clock);
	if (ret) {
		dev_err(dev, "Failed to set pixel clock to %ldHz: %d\n",
			dsip_clock, ret);
	}

	ret = clk_prepare_enable(dsi->pixel_clock);
	if (ret) {
		DRM_ERROR("Failed to turn on DSI pixel clock: %d\n", ret);
		return;
	}

	/* How many ns one DSI unit interval is.  Note that the clock
	 * is DDR, so there's an extra divide by 2.
	 */
	ui_ns = DIV_ROUND_UP(500000000, hs_clock);

	DSI_PORT_WRITE(HS_CLT0,
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 262, 0),
				     DSI_HS_CLT0_CZERO) |
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 0, 8),
				     DSI_HS_CLT0_CPRE) |
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 38, 0),
				     DSI_HS_CLT0_CPREP));

	DSI_PORT_WRITE(HS_CLT1,
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 60, 0),
				     DSI_HS_CLT1_CTRAIL) |
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 60, 52),
				     DSI_HS_CLT1_CPOST));

	DSI_PORT_WRITE(HS_CLT2,
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 1000000, 0),
				     DSI_HS_CLT2_WUP));

	DSI_PORT_WRITE(HS_DLT3,
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 100, 0),
				     DSI_HS_DLT3_EXIT) |
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 105, 6),
				     DSI_HS_DLT3_ZERO) |
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 40, 4),
				     DSI_HS_DLT3_PRE));

	DSI_PORT_WRITE(HS_DLT4,
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, lpx * ESC_TIME_NS, 0),
				     DSI_HS_DLT4_LPX) |
		       VC4_SET_FIELD(max(dsi_hs_timing(ui_ns, 0, 8),
					 dsi_hs_timing(ui_ns, 60, 4)),
				     DSI_HS_DLT4_TRAIL) |
		       VC4_SET_FIELD(0, DSI_HS_DLT4_ANLAT));

	/* T_INIT is how long STOP is driven after power-up to
	 * indicate to the slave (also coming out of power-up) that
	 * master init is complete, and should be greater than the
	 * maximum of two value: T_INIT,MASTER and T_INIT,SLAVE.  The
	 * D-PHY spec gives a minimum 100us for T_INIT,MASTER and
	 * T_INIT,SLAVE, while allowing protocols on top of it to give
	 * greater minimums.  The vc4 firmware uses an extremely
	 * conservative 5ms, and we maintain that here.
	 */
	DSI_PORT_WRITE(HS_DLT5, VC4_SET_FIELD(dsi_hs_timing(ui_ns,
							    5 * 1000 * 1000, 0),
					      DSI_HS_DLT5_INIT));

	DSI_PORT_WRITE(HS_DLT6,
		       VC4_SET_FIELD(lpx * 5, DSI_HS_DLT6_TA_GET) |
		       VC4_SET_FIELD(lpx, DSI_HS_DLT6_TA_SURE) |
		       VC4_SET_FIELD(lpx * 4, DSI_HS_DLT6_TA_GO) |
		       VC4_SET_FIELD(lpx, DSI_HS_DLT6_LP_LPX));

	DSI_PORT_WRITE(HS_DLT7,
		       VC4_SET_FIELD(dsi_esc_timing(1000000),
				     DSI_HS_DLT7_LP_WUP));

	DSI_PORT_WRITE(PHYC,
		       DSI_PHYC_DLANE0_ENABLE |
		       (dsi->lanes >= 2 ? DSI_PHYC_DLANE1_ENABLE : 0) |
		       (dsi->lanes >= 3 ? DSI_PHYC_DLANE2_ENABLE : 0) |
		       (dsi->lanes >= 4 ? DSI_PHYC_DLANE3_ENABLE : 0) |
		       DSI_PORT_BIT(PHYC_CLANE_ENABLE) |
		       ((dsi->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS) ?
			0 : DSI_PORT_BIT(PHYC_HS_CLK_CONTINUOUS)) |
		       (dsi->port == 0 ?
			VC4_SET_FIELD(lpx - 1, DSI0_PHYC_ESC_CLK_LPDT) :
			VC4_SET_FIELD(lpx - 1, DSI1_PHYC_ESC_CLK_LPDT)));

	DSI_PORT_WRITE(CTRL,
		       DSI_PORT_READ(CTRL) |
		       DSI_CTRL_CAL_BYTE);

	/* HS timeout in HS clock cycles: disabled. */
	DSI_PORT_WRITE(HSTX_TO_CNT, 0);
	/* LP receive timeout in HS clocks. */
	DSI_PORT_WRITE(LPRX_TO_CNT, 0xffffff);
	/* Bus turnaround timeout */
	DSI_PORT_WRITE(TA_TO_CNT, 100000);
	/* Display reset sequence timeout */
	DSI_PORT_WRITE(PR_TO_CNT, 100000);

	/* Set up DISP1 for transferring long command payloads through
	 * the pixfifo.
	 */
	DSI_PORT_WRITE(DISP1_CTRL,
		       VC4_SET_FIELD(DSI_DISP1_PFORMAT_32BIT_LE,
				     DSI_DISP1_PFORMAT) |
		       DSI_DISP1_ENABLE);

	/* Ungate the block. */
	if (dsi->port == 0)
		DSI_PORT_WRITE(CTRL, DSI_PORT_READ(CTRL) | DSI0_CTRL_CTRL0);
	else
		DSI_PORT_WRITE(CTRL, DSI_PORT_READ(CTRL) | DSI1_CTRL_EN);

	/* Bring AFE out of reset. */
	if (dsi->port == 0) {
	} else {
		DSI_PORT_WRITE(PHY_AFEC0,
			       DSI_PORT_READ(PHY_AFEC0) &
			       ~DSI1_PHY_AFEC0_RESET);
	}

	vc4_dsi_ulps(dsi, false);

	drm_bridge_pre_enable(dsi->bridge);

	if (dsi->mode_flags & MIPI_DSI_MODE_VIDEO) {
		DSI_PORT_WRITE(DISP0_CTRL,
			       VC4_SET_FIELD(dsi->divider,
					     DSI_DISP0_PIX_CLK_DIV) |
			       VC4_SET_FIELD(dsi->format, DSI_DISP0_PFORMAT) |
			       VC4_SET_FIELD(DSI_DISP0_LP_STOP_PERFRAME,
					     DSI_DISP0_LP_STOP_CTRL) |
			       DSI_DISP0_ST_END |
			       DSI_DISP0_ENABLE);
	} else {
		DSI_PORT_WRITE(DISP0_CTRL,
			       DSI_DISP0_COMMAND_MODE |
			       DSI_DISP0_ENABLE);
	}

	drm_bridge_enable(dsi->bridge);

	if (debug_dump_regs) {
		struct drm_printer p = drm_info_printer(&dsi->pdev->dev);
		dev_info(&dsi->pdev->dev, "DSI regs after:\n");
		drm_print_regset32(&p, &dsi->regset);
	}
}