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
struct sun8i_dw_hdmi {scalar_t__ ddc_en; int /*<<< orphan*/  regulator; int /*<<< orphan*/  rst_ctrl; int /*<<< orphan*/  clk_tmds; int /*<<< orphan*/  hdmi; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sun8i_dw_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dw_hdmi_unbind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun8i_hdmi_phy_remove (struct sun8i_dw_hdmi*) ; 

__attribute__((used)) static void sun8i_dw_hdmi_unbind(struct device *dev, struct device *master,
				 void *data)
{
	struct sun8i_dw_hdmi *hdmi = dev_get_drvdata(dev);

	dw_hdmi_unbind(hdmi->hdmi);
	sun8i_hdmi_phy_remove(hdmi);
	clk_disable_unprepare(hdmi->clk_tmds);
	reset_control_assert(hdmi->rst_ctrl);
	gpiod_set_value(hdmi->ddc_en, 0);
	regulator_disable(hdmi->regulator);

	if (hdmi->ddc_en)
		gpiod_put(hdmi->ddc_en);
}