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
struct TYPE_2__ {int /*<<< orphan*/  enc_out_bus_format; } ;
struct dw_hdmi {TYPE_1__ hdmi_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_CSC_CFG ; 
 int HDMI_CSC_CFG_DECMODE_CHROMA_INT_FORMULA3 ; 
 int HDMI_CSC_CFG_INTMODE_CHROMA_INT_FORMULA1 ; 
 int HDMI_CSC_CFG_INTMODE_DISABLE ; 
 int /*<<< orphan*/  HDMI_CSC_SCALE ; 
 int HDMI_CSC_SCALE_CSC_COLORDE_PTH_24BPP ; 
 int HDMI_CSC_SCALE_CSC_COLORDE_PTH_30BPP ; 
 int HDMI_CSC_SCALE_CSC_COLORDE_PTH_36BPP ; 
 int HDMI_CSC_SCALE_CSC_COLORDE_PTH_48BPP ; 
 int /*<<< orphan*/  HDMI_CSC_SCALE_CSC_COLORDE_PTH_MASK ; 
 int /*<<< orphan*/  dw_hdmi_update_csc_coeffs (struct dw_hdmi*) ; 
 int hdmi_bus_fmt_color_depth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_modb (struct dw_hdmi*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_color_space_decimation (struct dw_hdmi*) ; 
 scalar_t__ is_color_space_interpolation (struct dw_hdmi*) ; 

__attribute__((used)) static void hdmi_video_csc(struct dw_hdmi *hdmi)
{
	int color_depth = 0;
	int interpolation = HDMI_CSC_CFG_INTMODE_DISABLE;
	int decimation = 0;

	/* YCC422 interpolation to 444 mode */
	if (is_color_space_interpolation(hdmi))
		interpolation = HDMI_CSC_CFG_INTMODE_CHROMA_INT_FORMULA1;
	else if (is_color_space_decimation(hdmi))
		decimation = HDMI_CSC_CFG_DECMODE_CHROMA_INT_FORMULA3;

	switch (hdmi_bus_fmt_color_depth(hdmi->hdmi_data.enc_out_bus_format)) {
	case 8:
		color_depth = HDMI_CSC_SCALE_CSC_COLORDE_PTH_24BPP;
		break;
	case 10:
		color_depth = HDMI_CSC_SCALE_CSC_COLORDE_PTH_30BPP;
		break;
	case 12:
		color_depth = HDMI_CSC_SCALE_CSC_COLORDE_PTH_36BPP;
		break;
	case 16:
		color_depth = HDMI_CSC_SCALE_CSC_COLORDE_PTH_48BPP;
		break;

	default:
		return;
	}

	/* Configure the CSC registers */
	hdmi_writeb(hdmi, interpolation | decimation, HDMI_CSC_CFG);
	hdmi_modb(hdmi, color_depth, HDMI_CSC_SCALE_CSC_COLORDE_PTH_MASK,
		  HDMI_CSC_SCALE);

	dw_hdmi_update_csc_coeffs(hdmi);
}