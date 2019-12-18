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
typedef  int /*<<< orphan*/  u8 ;
struct dw_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_PHY_I2CM_SLAVE_ADDR ; 
 int /*<<< orphan*/  hdmi_phy_test_clear (struct dw_hdmi*,int) ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dw_hdmi_phy_i2c_set_addr(struct dw_hdmi *hdmi, u8 address)
{
	hdmi_phy_test_clear(hdmi, 1);
	hdmi_writeb(hdmi, address, HDMI_PHY_I2CM_SLAVE_ADDR);
	hdmi_phy_test_clear(hdmi, 0);
}