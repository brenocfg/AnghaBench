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
struct omap_hdmi {int core_enabled; int /*<<< orphan*/  vdda_reg; int /*<<< orphan*/  dss; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_HDMI_M_PCLK ; 
 int /*<<< orphan*/  dss_select_hdmi_venc_clk_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hdmi_runtime_get (struct omap_hdmi*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdmi_power_on_core(struct omap_hdmi *hdmi)
{
	int r;

	r = regulator_enable(hdmi->vdda_reg);
	if (r)
		return r;

	r = hdmi_runtime_get(hdmi);
	if (r)
		goto err_runtime_get;

	/* Make selection of HDMI in DSS */
	dss_select_hdmi_venc_clk_source(hdmi->dss, DSS_HDMI_M_PCLK);

	hdmi->core_enabled = true;

	return 0;

err_runtime_get:
	regulator_disable(hdmi->vdda_reg);

	return r;
}