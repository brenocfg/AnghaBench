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
struct hdmi_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_CORE_RSTOUT ; 
 int /*<<< orphan*/  HDMI_PHY_RSTOUT ; 
 int HDMI_PHY_SW_RSTOUT ; 
 int /*<<< orphan*/  hdmi_reg_writemask (struct hdmi_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void hdmiphy_conf_reset(struct hdmi_context *hdata)
{
	hdmi_reg_writemask(hdata, HDMI_CORE_RSTOUT, 0, 1);
	usleep_range(10000, 12000);
	hdmi_reg_writemask(hdata, HDMI_CORE_RSTOUT, ~0, 1);
	usleep_range(10000, 12000);
	hdmi_reg_writemask(hdata, HDMI_PHY_RSTOUT, ~0, HDMI_PHY_SW_RSTOUT);
	usleep_range(10000, 12000);
	hdmi_reg_writemask(hdata, HDMI_PHY_RSTOUT, 0, HDMI_PHY_SW_RSTOUT);
	usleep_range(10000, 12000);
}