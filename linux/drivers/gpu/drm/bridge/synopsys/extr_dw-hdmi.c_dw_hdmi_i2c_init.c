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
struct dw_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_I2CM_CTLINT ; 
 int HDMI_I2CM_CTLINT_ARB_POL ; 
 int HDMI_I2CM_CTLINT_NAC_POL ; 
 int /*<<< orphan*/  HDMI_I2CM_DIV ; 
 int /*<<< orphan*/  HDMI_I2CM_INT ; 
 int HDMI_I2CM_INT_DONE_POL ; 
 int /*<<< orphan*/  HDMI_I2CM_SOFTRSTZ ; 
 int /*<<< orphan*/  HDMI_IH_I2CM_STAT0 ; 
 int HDMI_IH_I2CM_STAT0_DONE ; 
 int HDMI_IH_I2CM_STAT0_ERROR ; 
 int /*<<< orphan*/  HDMI_IH_MUTE_I2CM_STAT0 ; 
 int /*<<< orphan*/  HDMI_PHY_I2CM_CTLINT_ADDR ; 
 int HDMI_PHY_I2CM_CTLINT_ADDR_ARBITRATION_POL ; 
 int HDMI_PHY_I2CM_CTLINT_ADDR_NAC_POL ; 
 int /*<<< orphan*/  HDMI_PHY_I2CM_INT_ADDR ; 
 int HDMI_PHY_I2CM_INT_ADDR_DONE_POL ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_hdmi_i2c_init(struct dw_hdmi *hdmi)
{
	hdmi_writeb(hdmi, HDMI_PHY_I2CM_INT_ADDR_DONE_POL,
		    HDMI_PHY_I2CM_INT_ADDR);

	hdmi_writeb(hdmi, HDMI_PHY_I2CM_CTLINT_ADDR_NAC_POL |
		    HDMI_PHY_I2CM_CTLINT_ADDR_ARBITRATION_POL,
		    HDMI_PHY_I2CM_CTLINT_ADDR);

	/* Software reset */
	hdmi_writeb(hdmi, 0x00, HDMI_I2CM_SOFTRSTZ);

	/* Set Standard Mode speed (determined to be 100KHz on iMX6) */
	hdmi_writeb(hdmi, 0x00, HDMI_I2CM_DIV);

	/* Set done, not acknowledged and arbitration interrupt polarities */
	hdmi_writeb(hdmi, HDMI_I2CM_INT_DONE_POL, HDMI_I2CM_INT);
	hdmi_writeb(hdmi, HDMI_I2CM_CTLINT_NAC_POL | HDMI_I2CM_CTLINT_ARB_POL,
		    HDMI_I2CM_CTLINT);

	/* Clear DONE and ERROR interrupts */
	hdmi_writeb(hdmi, HDMI_IH_I2CM_STAT0_ERROR | HDMI_IH_I2CM_STAT0_DONE,
		    HDMI_IH_I2CM_STAT0);

	/* Mute DONE and ERROR interrupts */
	hdmi_writeb(hdmi, HDMI_IH_I2CM_STAT0_ERROR | HDMI_IH_I2CM_STAT0_DONE,
		    HDMI_IH_MUTE_I2CM_STAT0);
}