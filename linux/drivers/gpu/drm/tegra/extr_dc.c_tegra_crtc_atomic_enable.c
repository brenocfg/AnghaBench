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
struct tegra_dc_state {int dummy; } ;
struct tegra_dc {TYPE_1__* soc; scalar_t__ syncpt; int /*<<< orphan*/  dev; } ;
struct drm_display_mode {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_2__* state; } ;
struct TYPE_4__ {struct drm_display_mode adjusted_mode; } ;
struct TYPE_3__ {scalar_t__ has_nvdisplay; scalar_t__ supports_interlacing; scalar_t__ supports_background_color; } ;

/* Variables and functions */
 int CURSOR_THRESHOLD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_CMD_CONT_SYNCPT_VSYNC ; 
 int /*<<< orphan*/  DC_CMD_DISPLAY_COMMAND ; 
 int /*<<< orphan*/  DC_CMD_DISPLAY_POWER_CONTROL ; 
 int /*<<< orphan*/  DC_CMD_GENERAL_INCR_SYNCPT_CNTRL ; 
 int /*<<< orphan*/  DC_CMD_INT_ENABLE ; 
 int /*<<< orphan*/  DC_CMD_INT_MASK ; 
 int /*<<< orphan*/  DC_CMD_INT_POLARITY ; 
 int /*<<< orphan*/  DC_CMD_INT_TYPE ; 
 int /*<<< orphan*/  DC_CMD_STATE_ACCESS ; 
 int /*<<< orphan*/  DC_COM_RG_UNDERFLOW ; 
 int /*<<< orphan*/  DC_DISP_BLEND_BACKGROUND_COLOR ; 
 int /*<<< orphan*/  DC_DISP_BORDER_COLOR ; 
 int /*<<< orphan*/  DC_DISP_DISP_MEM_HIGH_PRIORITY ; 
 int /*<<< orphan*/  DC_DISP_DISP_MEM_HIGH_PRIORITY_TIMER ; 
 int /*<<< orphan*/  DC_DISP_INTERLACE_CONTROL ; 
 int DISP_CTRL_MODE_C_DISPLAY ; 
 int DISP_CTRL_MODE_MASK ; 
 int DSC_BBUF_UF_INT ; 
 int DSC_OBUF_UF_INT ; 
 int DSC_RBUF_UF_INT ; 
 int DSC_TO_UF_INT ; 
 int FRAME_END_INT ; 
 int HEAD_UF_INT ; 
 int INTERLACE_ENABLE ; 
 int MSF_INT ; 
 int PM0_ENABLE ; 
 int PM1_ENABLE ; 
 int PW0_ENABLE ; 
 int PW1_ENABLE ; 
 int PW2_ENABLE ; 
 int PW3_ENABLE ; 
 int PW4_ENABLE ; 
 int READ_MUX ; 
 int REGION_CRC_INT ; 
 int REG_TMOUT_INT ; 
 int SD3_BUCKET_WALK_DONE_INT ; 
 int SYNCPT_CNTRL_NO_STALL ; 
 int UNDERFLOW_MODE_RED ; 
 int UNDERFLOW_REPORT_ENABLE ; 
 int VBLANK_INT ; 
 int V_PULSE2_INT ; 
 int V_PULSE3_INT ; 
 int WINDOW_A_THRESHOLD (int) ; 
 int WINDOW_B_THRESHOLD (int) ; 
 int WINDOW_C_THRESHOLD (int) ; 
 int WIN_A_OF_INT ; 
 int WIN_A_UF_INT ; 
 int WIN_B_OF_INT ; 
 int WIN_B_UF_INT ; 
 int WIN_C_OF_INT ; 
 int WIN_C_UF_INT ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int host1x_syncpt_id (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_commit (struct tegra_dc*) ; 
 int /*<<< orphan*/  tegra_dc_commit_state (struct tegra_dc*,struct tegra_dc_state*) ; 
 int tegra_dc_readl (struct tegra_dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_set_timings (struct tegra_dc*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int,int /*<<< orphan*/ ) ; 
 struct tegra_dc_state* to_dc_state (TYPE_2__*) ; 
 struct tegra_dc* to_tegra_dc (struct drm_crtc*) ; 

__attribute__((used)) static void tegra_crtc_atomic_enable(struct drm_crtc *crtc,
				     struct drm_crtc_state *old_state)
{
	struct drm_display_mode *mode = &crtc->state->adjusted_mode;
	struct tegra_dc_state *state = to_dc_state(crtc->state);
	struct tegra_dc *dc = to_tegra_dc(crtc);
	u32 value;

	pm_runtime_get_sync(dc->dev);

	/* initialize display controller */
	if (dc->syncpt) {
		u32 syncpt = host1x_syncpt_id(dc->syncpt), enable;

		if (dc->soc->has_nvdisplay)
			enable = 1 << 31;
		else
			enable = 1 << 8;

		value = SYNCPT_CNTRL_NO_STALL;
		tegra_dc_writel(dc, value, DC_CMD_GENERAL_INCR_SYNCPT_CNTRL);

		value = enable | syncpt;
		tegra_dc_writel(dc, value, DC_CMD_CONT_SYNCPT_VSYNC);
	}

	if (dc->soc->has_nvdisplay) {
		value = DSC_TO_UF_INT | DSC_BBUF_UF_INT | DSC_RBUF_UF_INT |
			DSC_OBUF_UF_INT;
		tegra_dc_writel(dc, value, DC_CMD_INT_TYPE);

		value = DSC_TO_UF_INT | DSC_BBUF_UF_INT | DSC_RBUF_UF_INT |
			DSC_OBUF_UF_INT | SD3_BUCKET_WALK_DONE_INT |
			HEAD_UF_INT | MSF_INT | REG_TMOUT_INT |
			REGION_CRC_INT | V_PULSE2_INT | V_PULSE3_INT |
			VBLANK_INT | FRAME_END_INT;
		tegra_dc_writel(dc, value, DC_CMD_INT_POLARITY);

		value = SD3_BUCKET_WALK_DONE_INT | HEAD_UF_INT | VBLANK_INT |
			FRAME_END_INT;
		tegra_dc_writel(dc, value, DC_CMD_INT_ENABLE);

		value = HEAD_UF_INT | REG_TMOUT_INT | FRAME_END_INT;
		tegra_dc_writel(dc, value, DC_CMD_INT_MASK);

		tegra_dc_writel(dc, READ_MUX, DC_CMD_STATE_ACCESS);
	} else {
		value = WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT |
			WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT;
		tegra_dc_writel(dc, value, DC_CMD_INT_TYPE);

		value = WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT |
			WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT;
		tegra_dc_writel(dc, value, DC_CMD_INT_POLARITY);

		/* initialize timer */
		value = CURSOR_THRESHOLD(0) | WINDOW_A_THRESHOLD(0x20) |
			WINDOW_B_THRESHOLD(0x20) | WINDOW_C_THRESHOLD(0x20);
		tegra_dc_writel(dc, value, DC_DISP_DISP_MEM_HIGH_PRIORITY);

		value = CURSOR_THRESHOLD(0) | WINDOW_A_THRESHOLD(1) |
			WINDOW_B_THRESHOLD(1) | WINDOW_C_THRESHOLD(1);
		tegra_dc_writel(dc, value, DC_DISP_DISP_MEM_HIGH_PRIORITY_TIMER);

		value = VBLANK_INT | WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT |
			WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT;
		tegra_dc_writel(dc, value, DC_CMD_INT_ENABLE);

		value = WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT |
			WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT;
		tegra_dc_writel(dc, value, DC_CMD_INT_MASK);
	}

	if (dc->soc->supports_background_color)
		tegra_dc_writel(dc, 0, DC_DISP_BLEND_BACKGROUND_COLOR);
	else
		tegra_dc_writel(dc, 0, DC_DISP_BORDER_COLOR);

	/* apply PLL and pixel clock changes */
	tegra_dc_commit_state(dc, state);

	/* program display mode */
	tegra_dc_set_timings(dc, mode);

	/* interlacing isn't supported yet, so disable it */
	if (dc->soc->supports_interlacing) {
		value = tegra_dc_readl(dc, DC_DISP_INTERLACE_CONTROL);
		value &= ~INTERLACE_ENABLE;
		tegra_dc_writel(dc, value, DC_DISP_INTERLACE_CONTROL);
	}

	value = tegra_dc_readl(dc, DC_CMD_DISPLAY_COMMAND);
	value &= ~DISP_CTRL_MODE_MASK;
	value |= DISP_CTRL_MODE_C_DISPLAY;
	tegra_dc_writel(dc, value, DC_CMD_DISPLAY_COMMAND);

	if (!dc->soc->has_nvdisplay) {
		value = tegra_dc_readl(dc, DC_CMD_DISPLAY_POWER_CONTROL);
		value |= PW0_ENABLE | PW1_ENABLE | PW2_ENABLE | PW3_ENABLE |
			 PW4_ENABLE | PM0_ENABLE | PM1_ENABLE;
		tegra_dc_writel(dc, value, DC_CMD_DISPLAY_POWER_CONTROL);
	}

	/* enable underflow reporting and display red for missing pixels */
	if (dc->soc->has_nvdisplay) {
		value = UNDERFLOW_MODE_RED | UNDERFLOW_REPORT_ENABLE;
		tegra_dc_writel(dc, value, DC_COM_RG_UNDERFLOW);
	}

	tegra_dc_commit(dc);

	drm_crtc_vblank_on(crtc);
}