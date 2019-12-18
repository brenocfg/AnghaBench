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
struct hdmi_context {scalar_t__ regs_hdmiphy; int /*<<< orphan*/ * drv_data; } ;

/* Variables and functions */
 scalar_t__ HDMIPHY5433_MODE_SET_DONE ; 
 int /*<<< orphan*/  HDMI_PHY_DISABLE_MODE_SET ; 
 int /*<<< orphan*/  HDMI_PHY_ENABLE_MODE_SET ; 
 int /*<<< orphan*/  exynos5433_hdmi_driver_data ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hdmiphy_enable_mode_set(struct hdmi_context *hdata, bool enable)
{
	u8 v = enable ? HDMI_PHY_ENABLE_MODE_SET : HDMI_PHY_DISABLE_MODE_SET;

	if (hdata->drv_data == &exynos5433_hdmi_driver_data)
		writel(v, hdata->regs_hdmiphy + HDMIPHY5433_MODE_SET_DONE);
}