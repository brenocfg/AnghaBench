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
typedef  scalar_t__ uint32_t ;
typedef  struct spread_spectrum_data {scalar_t__ freq_range_khz; } const spread_spectrum_data ;
struct dce110_clk_src {scalar_t__ dvi_ss_params_cnt; scalar_t__ hdmi_ss_params_cnt; scalar_t__ dp_ss_params_cnt; struct spread_spectrum_data const* dp_ss_params; struct spread_spectrum_data const* hdmi_ss_params; struct spread_spectrum_data const* dvi_ss_params; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;

/* Variables and functions */
#define  SIGNAL_TYPE_DISPLAY_PORT 134 
#define  SIGNAL_TYPE_DISPLAY_PORT_MST 133 
#define  SIGNAL_TYPE_DVI_DUAL_LINK 132 
#define  SIGNAL_TYPE_DVI_SINGLE_LINK 131 
#define  SIGNAL_TYPE_EDP 130 
#define  SIGNAL_TYPE_HDMI_TYPE_A 129 
#define  SIGNAL_TYPE_VIRTUAL 128 

__attribute__((used)) static const struct spread_spectrum_data *get_ss_data_entry(
		struct dce110_clk_src *clk_src,
		enum signal_type signal,
		uint32_t pix_clk_khz)
{

	uint32_t entrys_num;
	uint32_t i;
	struct spread_spectrum_data *ss_parm = NULL;
	struct spread_spectrum_data *ret = NULL;

	switch (signal) {
	case SIGNAL_TYPE_DVI_SINGLE_LINK:
	case SIGNAL_TYPE_DVI_DUAL_LINK:
		ss_parm = clk_src->dvi_ss_params;
		entrys_num = clk_src->dvi_ss_params_cnt;
		break;

	case SIGNAL_TYPE_HDMI_TYPE_A:
		ss_parm = clk_src->hdmi_ss_params;
		entrys_num = clk_src->hdmi_ss_params_cnt;
		break;

	case SIGNAL_TYPE_DISPLAY_PORT:
	case SIGNAL_TYPE_DISPLAY_PORT_MST:
	case SIGNAL_TYPE_EDP:
	case SIGNAL_TYPE_VIRTUAL:
		ss_parm = clk_src->dp_ss_params;
		entrys_num = clk_src->dp_ss_params_cnt;
		break;

	default:
		ss_parm = NULL;
		entrys_num = 0;
		break;
	}

	if (ss_parm == NULL)
		return ret;

	for (i = 0; i < entrys_num; ++i, ++ss_parm) {
		if (ss_parm->freq_range_khz >= pix_clk_khz) {
			ret = ss_parm;
			break;
		}
	}

	return ret;
}