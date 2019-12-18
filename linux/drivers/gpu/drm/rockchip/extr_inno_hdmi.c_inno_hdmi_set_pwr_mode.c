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
struct inno_hdmi {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  HDMI_PHY_CHG_PWR ; 
 int /*<<< orphan*/  HDMI_PHY_DRIVER ; 
 int /*<<< orphan*/  HDMI_PHY_PRE_EMPHASIS ; 
 int /*<<< orphan*/  HDMI_PHY_SYNC ; 
 int /*<<< orphan*/  HDMI_PHY_SYS_CTL ; 
#define  LOWER_PWR 129 
#define  NORMAL 128 
 int /*<<< orphan*/  hdmi_writeb (struct inno_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inno_hdmi_sys_power (struct inno_hdmi*,int) ; 

__attribute__((used)) static void inno_hdmi_set_pwr_mode(struct inno_hdmi *hdmi, int mode)
{
	switch (mode) {
	case NORMAL:
		inno_hdmi_sys_power(hdmi, false);

		hdmi_writeb(hdmi, HDMI_PHY_PRE_EMPHASIS, 0x6f);
		hdmi_writeb(hdmi, HDMI_PHY_DRIVER, 0xbb);

		hdmi_writeb(hdmi, HDMI_PHY_SYS_CTL, 0x15);
		hdmi_writeb(hdmi, HDMI_PHY_SYS_CTL, 0x14);
		hdmi_writeb(hdmi, HDMI_PHY_SYS_CTL, 0x10);
		hdmi_writeb(hdmi, HDMI_PHY_CHG_PWR, 0x0f);
		hdmi_writeb(hdmi, HDMI_PHY_SYNC, 0x00);
		hdmi_writeb(hdmi, HDMI_PHY_SYNC, 0x01);

		inno_hdmi_sys_power(hdmi, true);
		break;

	case LOWER_PWR:
		inno_hdmi_sys_power(hdmi, false);
		hdmi_writeb(hdmi, HDMI_PHY_DRIVER, 0x00);
		hdmi_writeb(hdmi, HDMI_PHY_PRE_EMPHASIS, 0x00);
		hdmi_writeb(hdmi, HDMI_PHY_CHG_PWR, 0x00);
		hdmi_writeb(hdmi, HDMI_PHY_SYS_CTL, 0x15);

		break;

	default:
		DRM_DEV_ERROR(hdmi->dev, "Unknown power mode %d\n", mode);
	}
}