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
struct dw_hdmi {int phy_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_IH_MUTE_PHY_STAT0 ; 
 int /*<<< orphan*/  HDMI_IH_PHY_STAT0 ; 
 int HDMI_IH_PHY_STAT0_HPD ; 
 int HDMI_IH_PHY_STAT0_RX_SENSE ; 
 int HDMI_PHY_HPD ; 
 int /*<<< orphan*/  HDMI_PHY_MASK0 ; 
 int /*<<< orphan*/  HDMI_PHY_POL0 ; 
 int HDMI_PHY_RX_SENSE ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int,int /*<<< orphan*/ ) ; 

void dw_hdmi_phy_setup_hpd(struct dw_hdmi *hdmi, void *data)
{
	/*
	 * Configure the PHY RX SENSE and HPD interrupts polarities and clear
	 * any pending interrupt.
	 */
	hdmi_writeb(hdmi, HDMI_PHY_HPD | HDMI_PHY_RX_SENSE, HDMI_PHY_POL0);
	hdmi_writeb(hdmi, HDMI_IH_PHY_STAT0_HPD | HDMI_IH_PHY_STAT0_RX_SENSE,
		    HDMI_IH_PHY_STAT0);

	/* Enable cable hot plug irq. */
	hdmi_writeb(hdmi, hdmi->phy_mask, HDMI_PHY_MASK0);

	/* Clear and unmute interrupts. */
	hdmi_writeb(hdmi, HDMI_IH_PHY_STAT0_HPD | HDMI_IH_PHY_STAT0_RX_SENSE,
		    HDMI_IH_PHY_STAT0);
	hdmi_writeb(hdmi, ~(HDMI_IH_PHY_STAT0_HPD | HDMI_IH_PHY_STAT0_RX_SENSE),
		    HDMI_IH_MUTE_PHY_STAT0);
}