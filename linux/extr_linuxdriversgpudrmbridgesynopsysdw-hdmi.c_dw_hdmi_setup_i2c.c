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
 int /*<<< orphan*/  HDMI_PHY_I2CM_CTLINT_ADDR ; 
 int HDMI_PHY_I2CM_CTLINT_ADDR_ARBITRATION_POL ; 
 int HDMI_PHY_I2CM_CTLINT_ADDR_NAC_POL ; 
 int /*<<< orphan*/  HDMI_PHY_I2CM_INT_ADDR ; 
 int HDMI_PHY_I2CM_INT_ADDR_DONE_POL ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_hdmi_setup_i2c(struct dw_hdmi *hdmi)
{
	hdmi_writeb(hdmi, HDMI_PHY_I2CM_INT_ADDR_DONE_POL,
		    HDMI_PHY_I2CM_INT_ADDR);

	hdmi_writeb(hdmi, HDMI_PHY_I2CM_CTLINT_ADDR_NAC_POL |
		    HDMI_PHY_I2CM_CTLINT_ADDR_ARBITRATION_POL,
		    HDMI_PHY_I2CM_CTLINT_ADDR);
}