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
typedef  int /*<<< orphan*/  u16 ;
struct rk3066_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_SYS_CTRL ; 
 int /*<<< orphan*/  HDMI_SYS_PLL_RESET ; 
 int /*<<< orphan*/  HDMI_SYS_PLL_RESET_MASK ; 
 int /*<<< orphan*/  hdmi_modb (struct rk3066_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct rk3066_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void
rk3066_hdmi_phy_write(struct rk3066_hdmi *hdmi, u16 offset, u8 value)
{
	hdmi_writeb(hdmi, offset, value);
	hdmi_modb(hdmi, HDMI_SYS_CTRL,
		  HDMI_SYS_PLL_RESET_MASK, HDMI_SYS_PLL_RESET);
	usleep_range(90, 100);
	hdmi_modb(hdmi, HDMI_SYS_CTRL, HDMI_SYS_PLL_RESET_MASK, 0);
	usleep_range(900, 1000);
}