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
struct dw_hdmi {int mc_clkdis; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_FC_CH0PREAM ; 
 int /*<<< orphan*/  HDMI_FC_CH1PREAM ; 
 int /*<<< orphan*/  HDMI_FC_CH2PREAM ; 
 int /*<<< orphan*/  HDMI_FC_CTRLDUR ; 
 int /*<<< orphan*/  HDMI_FC_EXCTRLDUR ; 
 int /*<<< orphan*/  HDMI_FC_EXCTRLSPAC ; 
 int /*<<< orphan*/  HDMI_MC_CLKDIS ; 
 int HDMI_MC_CLKDIS_AUDCLK_DISABLE ; 
 int HDMI_MC_CLKDIS_CSCCLK_DISABLE ; 
 int HDMI_MC_CLKDIS_HDCPCLK_DISABLE ; 
 int HDMI_MC_CLKDIS_PIXELCLK_DISABLE ; 
 int HDMI_MC_CLKDIS_PREPCLK_DISABLE ; 
 int HDMI_MC_CLKDIS_TMDSCLK_DISABLE ; 
 int /*<<< orphan*/  HDMI_MC_FLOWCTRL ; 
 int HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_BYPASS ; 
 int HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_IN_PATH ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_color_space_conversion (struct dw_hdmi*) ; 

__attribute__((used)) static void dw_hdmi_enable_video_path(struct dw_hdmi *hdmi)
{
	/* control period minimum duration */
	hdmi_writeb(hdmi, 12, HDMI_FC_CTRLDUR);
	hdmi_writeb(hdmi, 32, HDMI_FC_EXCTRLDUR);
	hdmi_writeb(hdmi, 1, HDMI_FC_EXCTRLSPAC);

	/* Set to fill TMDS data channels */
	hdmi_writeb(hdmi, 0x0B, HDMI_FC_CH0PREAM);
	hdmi_writeb(hdmi, 0x16, HDMI_FC_CH1PREAM);
	hdmi_writeb(hdmi, 0x21, HDMI_FC_CH2PREAM);

	/* Enable pixel clock and tmds data path */
	hdmi->mc_clkdis |= HDMI_MC_CLKDIS_HDCPCLK_DISABLE |
			   HDMI_MC_CLKDIS_CSCCLK_DISABLE |
			   HDMI_MC_CLKDIS_AUDCLK_DISABLE |
			   HDMI_MC_CLKDIS_PREPCLK_DISABLE |
			   HDMI_MC_CLKDIS_TMDSCLK_DISABLE;
	hdmi->mc_clkdis &= ~HDMI_MC_CLKDIS_PIXELCLK_DISABLE;
	hdmi_writeb(hdmi, hdmi->mc_clkdis, HDMI_MC_CLKDIS);

	hdmi->mc_clkdis &= ~HDMI_MC_CLKDIS_TMDSCLK_DISABLE;
	hdmi_writeb(hdmi, hdmi->mc_clkdis, HDMI_MC_CLKDIS);

	/* Enable csc path */
	if (is_color_space_conversion(hdmi)) {
		hdmi->mc_clkdis &= ~HDMI_MC_CLKDIS_CSCCLK_DISABLE;
		hdmi_writeb(hdmi, hdmi->mc_clkdis, HDMI_MC_CLKDIS);
	}

	/* Enable color space conversion if needed */
	if (is_color_space_conversion(hdmi))
		hdmi_writeb(hdmi, HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_IN_PATH,
			    HDMI_MC_FLOWCTRL);
	else
		hdmi_writeb(hdmi, HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_BYPASS,
			    HDMI_MC_FLOWCTRL);
}