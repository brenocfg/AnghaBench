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
struct hdmi_context {int /*<<< orphan*/  sysreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS5433_SYSREG_DISP_HDMI_PHY ; 
 int /*<<< orphan*/  SYSREG_HDMI_REFCLK_INT_CLK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_set_refclk(struct hdmi_context *hdata, bool on)
{
	if (!hdata->sysreg)
		return;

	regmap_update_bits(hdata->sysreg, EXYNOS5433_SYSREG_DISP_HDMI_PHY,
			   SYSREG_HDMI_REFCLK_INT_CLK, on ? ~0 : 0);
}