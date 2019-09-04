#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dss_device {TYPE_1__* feat; } ;
typedef  enum omap_dss_output_id { ____Placeholder_omap_dss_output_id } omap_dss_output_id ;
typedef  enum dss_hdmi_venc_clk_source_select { ____Placeholder_dss_hdmi_venc_clk_source_select } dss_hdmi_venc_clk_source_select ;
struct TYPE_2__ {int* outputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_CONTROL ; 
 int DSS_HDMI_M_PCLK ; 
 int DSS_VENC_TV_CLK ; 
 size_t OMAP_DSS_CHANNEL_DIGIT ; 
 int OMAP_DSS_OUTPUT_HDMI ; 
 int OMAP_DSS_OUTPUT_VENC ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dss_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

void dss_select_hdmi_venc_clk_source(struct dss_device *dss,
				     enum dss_hdmi_venc_clk_source_select src)
{
	enum omap_dss_output_id outputs;

	outputs = dss->feat->outputs[OMAP_DSS_CHANNEL_DIGIT];

	/* Complain about invalid selections */
	WARN_ON((src == DSS_VENC_TV_CLK) && !(outputs & OMAP_DSS_OUTPUT_VENC));
	WARN_ON((src == DSS_HDMI_M_PCLK) && !(outputs & OMAP_DSS_OUTPUT_HDMI));

	/* Select only if we have options */
	if ((outputs & OMAP_DSS_OUTPUT_VENC) &&
	    (outputs & OMAP_DSS_OUTPUT_HDMI))
		/* VENC_HDMI_SWITCH */
		REG_FLD_MOD(dss, DSS_CONTROL, src, 15, 15);
}