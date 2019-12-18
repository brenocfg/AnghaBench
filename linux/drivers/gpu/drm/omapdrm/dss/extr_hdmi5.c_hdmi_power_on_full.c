#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct videomode {unsigned int pixelclock; int flags; int /*<<< orphan*/  vactive; int /*<<< orphan*/  hactive; } ;
struct TYPE_9__ {int /*<<< orphan*/  clkin; } ;
struct TYPE_7__ {TYPE_3__ pll; } ;
struct TYPE_8__ {struct videomode vm; } ;
struct omap_hdmi {TYPE_1__ pll; int /*<<< orphan*/  wp; int /*<<< orphan*/  output; TYPE_2__ cfg; int /*<<< orphan*/  core; int /*<<< orphan*/  phy; } ;
struct dss_pll_clock_info {int /*<<< orphan*/ * clkout; int /*<<< orphan*/  clkdco; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_DOUBLECLK ; 
 int /*<<< orphan*/  DSSDBG (char*,...) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EIO ; 
 int HDMI_IRQ_LINK_CONNECT ; 
 int HDMI_IRQ_LINK_DISCONNECT ; 
 int /*<<< orphan*/  HDMI_PHYPWRCMD_LDOON ; 
 int /*<<< orphan*/  HDMI_PHYPWRCMD_OFF ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_mgr_disable (int /*<<< orphan*/ *) ; 
 int dss_mgr_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dss_pll_calc_b (TYPE_3__*,int /*<<< orphan*/ ,unsigned int,struct dss_pll_clock_info*) ; 
 int /*<<< orphan*/  dss_pll_disable (TYPE_3__*) ; 
 int dss_pll_enable (TYPE_3__*) ; 
 int dss_pll_set_config (TYPE_3__*,struct dss_pll_clock_info*) ; 
 int /*<<< orphan*/  hdmi5_configure (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int hdmi_phy_configure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_power_off_core (struct omap_hdmi*) ; 
 int hdmi_power_on_core (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_wp_clear_irqenable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hdmi_wp_get_irqstatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_wp_set_irqenable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hdmi_wp_set_irqstatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hdmi_wp_set_phy_pwr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hdmi_wp_video_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdmi_power_on_full(struct omap_hdmi *hdmi)
{
	int r;
	const struct videomode *vm;
	struct dss_pll_clock_info hdmi_cinfo = { 0 };
	unsigned int pc;

	r = hdmi_power_on_core(hdmi);
	if (r)
		return r;

	vm = &hdmi->cfg.vm;

	DSSDBG("hdmi_power_on hactive= %d vactive = %d\n", vm->hactive,
	       vm->vactive);

	pc = vm->pixelclock;
	if (vm->flags & DISPLAY_FLAGS_DOUBLECLK)
		pc *= 2;

	/* DSS_HDMI_TCLK is bitclk / 10 */
	pc *= 10;

	dss_pll_calc_b(&hdmi->pll.pll, clk_get_rate(hdmi->pll.pll.clkin),
		pc, &hdmi_cinfo);

	/* disable and clear irqs */
	hdmi_wp_clear_irqenable(&hdmi->wp, 0xffffffff);
	hdmi_wp_set_irqstatus(&hdmi->wp,
			hdmi_wp_get_irqstatus(&hdmi->wp));

	r = dss_pll_enable(&hdmi->pll.pll);
	if (r) {
		DSSERR("Failed to enable PLL\n");
		goto err_pll_enable;
	}

	r = dss_pll_set_config(&hdmi->pll.pll, &hdmi_cinfo);
	if (r) {
		DSSERR("Failed to configure PLL\n");
		goto err_pll_cfg;
	}

	r = hdmi_phy_configure(&hdmi->phy, hdmi_cinfo.clkdco,
		hdmi_cinfo.clkout[0]);
	if (r) {
		DSSDBG("Failed to start PHY\n");
		goto err_phy_cfg;
	}

	r = hdmi_wp_set_phy_pwr(&hdmi->wp, HDMI_PHYPWRCMD_LDOON);
	if (r)
		goto err_phy_pwr;

	hdmi5_configure(&hdmi->core, &hdmi->wp, &hdmi->cfg);

	r = dss_mgr_enable(&hdmi->output);
	if (r)
		goto err_mgr_enable;

	r = hdmi_wp_video_start(&hdmi->wp);
	if (r)
		goto err_vid_enable;

	hdmi_wp_set_irqenable(&hdmi->wp,
			HDMI_IRQ_LINK_CONNECT | HDMI_IRQ_LINK_DISCONNECT);

	return 0;

err_vid_enable:
	dss_mgr_disable(&hdmi->output);
err_mgr_enable:
	hdmi_wp_set_phy_pwr(&hdmi->wp, HDMI_PHYPWRCMD_OFF);
err_phy_pwr:
err_phy_cfg:
err_pll_cfg:
	dss_pll_disable(&hdmi->pll.pll);
err_pll_enable:
	hdmi_power_off_core(hdmi);
	return -EIO;
}