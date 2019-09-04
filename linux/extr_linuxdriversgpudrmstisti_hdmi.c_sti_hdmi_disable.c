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
struct sti_hdmi {int enabled; int /*<<< orphan*/  notifier; int /*<<< orphan*/  clk_pix; int /*<<< orphan*/  clk_tmds; int /*<<< orphan*/  clk_phy; TYPE_1__* phy_ops; } ;
struct drm_bridge {struct sti_hdmi* driver_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) (struct sti_hdmi*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_PHYS_ADDR_INVALID ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  HDMI_CFG ; 
 int HDMI_CFG_DEVICE_EN ; 
 int /*<<< orphan*/  HDMI_DFLT_CHL0_DAT ; 
 int /*<<< orphan*/  HDMI_DFLT_CHL1_DAT ; 
 int /*<<< orphan*/  HDMI_DFLT_CHL2_DAT ; 
 int /*<<< orphan*/  HDMI_IFRAME_SLOT_AUDIO ; 
 int /*<<< orphan*/  HDMI_IFRAME_SLOT_AVI ; 
 int /*<<< orphan*/  HDMI_IFRAME_SLOT_VENDOR ; 
 int /*<<< orphan*/  HDMI_INT_CLR ; 
 int /*<<< orphan*/  cec_notifier_set_phys_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_infoframe_reset (struct sti_hdmi*,int /*<<< orphan*/ ) ; 
 int hdmi_read (struct sti_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write (struct sti_hdmi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sti_hdmi*) ; 

__attribute__((used)) static void sti_hdmi_disable(struct drm_bridge *bridge)
{
	struct sti_hdmi *hdmi = bridge->driver_private;

	u32 val = hdmi_read(hdmi, HDMI_CFG);

	if (!hdmi->enabled)
		return;

	DRM_DEBUG_DRIVER("\n");

	/* Disable HDMI */
	val &= ~HDMI_CFG_DEVICE_EN;
	hdmi_write(hdmi, val, HDMI_CFG);

	hdmi_write(hdmi, 0xffffffff, HDMI_INT_CLR);

	/* Stop the phy */
	hdmi->phy_ops->stop(hdmi);

	/* Reset info frame transmission */
	hdmi_infoframe_reset(hdmi, HDMI_IFRAME_SLOT_AVI);
	hdmi_infoframe_reset(hdmi, HDMI_IFRAME_SLOT_AUDIO);
	hdmi_infoframe_reset(hdmi, HDMI_IFRAME_SLOT_VENDOR);

	/* Set the default channel data to be a dark red */
	hdmi_write(hdmi, 0x0000, HDMI_DFLT_CHL0_DAT);
	hdmi_write(hdmi, 0x0000, HDMI_DFLT_CHL1_DAT);
	hdmi_write(hdmi, 0x0060, HDMI_DFLT_CHL2_DAT);

	/* Disable/unprepare hdmi clock */
	clk_disable_unprepare(hdmi->clk_phy);
	clk_disable_unprepare(hdmi->clk_tmds);
	clk_disable_unprepare(hdmi->clk_pix);

	hdmi->enabled = false;

	cec_notifier_set_phys_addr(hdmi->notifier, CEC_PHYS_ADDR_INVALID);
}