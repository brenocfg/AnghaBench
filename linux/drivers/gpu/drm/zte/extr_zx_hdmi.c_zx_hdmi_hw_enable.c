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
struct zx_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKPWD ; 
 int /*<<< orphan*/  CLKPWD_PDIDCK ; 
 int /*<<< orphan*/  FUNC_HDMI_EN ; 
 int /*<<< orphan*/  FUNC_SEL ; 
 int /*<<< orphan*/  HDMICTL4 ; 
 int /*<<< orphan*/  INTR1_MASK ; 
 int /*<<< orphan*/  INTR1_MONITOR_DETECT ; 
 int /*<<< orphan*/  P2T_CTRL ; 
 int /*<<< orphan*/  P2T_DC_PKT_EN ; 
 int /*<<< orphan*/  TEST_TXCTRL ; 
 int /*<<< orphan*/  TEST_TXCTRL_HDMI_MODE ; 
 int /*<<< orphan*/  hdmi_writeb (struct zx_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdmi_writeb_mask (struct zx_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx_hdmi_phy_start (struct zx_hdmi*) ; 

__attribute__((used)) static void zx_hdmi_hw_enable(struct zx_hdmi *hdmi)
{
	/* Enable pclk */
	hdmi_writeb_mask(hdmi, CLKPWD, CLKPWD_PDIDCK, CLKPWD_PDIDCK);

	/* Enable HDMI for TX */
	hdmi_writeb_mask(hdmi, FUNC_SEL, FUNC_HDMI_EN, FUNC_HDMI_EN);

	/* Enable deep color packet */
	hdmi_writeb_mask(hdmi, P2T_CTRL, P2T_DC_PKT_EN, P2T_DC_PKT_EN);

	/* Enable HDMI/MHL mode for output */
	hdmi_writeb_mask(hdmi, TEST_TXCTRL, TEST_TXCTRL_HDMI_MODE,
			 TEST_TXCTRL_HDMI_MODE);

	/* Configure reg_qc_sel */
	hdmi_writeb(hdmi, HDMICTL4, 0x3);

	/* Enable interrupt */
	hdmi_writeb_mask(hdmi, INTR1_MASK, INTR1_MONITOR_DETECT,
			 INTR1_MONITOR_DETECT);

	/* Start up phy */
	zx_hdmi_phy_start(hdmi);
}