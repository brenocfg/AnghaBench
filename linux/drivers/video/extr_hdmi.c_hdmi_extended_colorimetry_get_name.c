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
typedef  enum hdmi_extended_colorimetry { ____Placeholder_hdmi_extended_colorimetry } hdmi_extended_colorimetry ;

/* Variables and functions */
#define  HDMI_EXTENDED_COLORIMETRY_BT2020 135 
#define  HDMI_EXTENDED_COLORIMETRY_BT2020_CONST_LUM 134 
#define  HDMI_EXTENDED_COLORIMETRY_OPRGB 133 
#define  HDMI_EXTENDED_COLORIMETRY_OPYCC_601 132 
#define  HDMI_EXTENDED_COLORIMETRY_RESERVED 131 
#define  HDMI_EXTENDED_COLORIMETRY_S_YCC_601 130 
#define  HDMI_EXTENDED_COLORIMETRY_XV_YCC_601 129 
#define  HDMI_EXTENDED_COLORIMETRY_XV_YCC_709 128 

__attribute__((used)) static const char *
hdmi_extended_colorimetry_get_name(enum hdmi_extended_colorimetry ext_col)
{
	switch (ext_col) {
	case HDMI_EXTENDED_COLORIMETRY_XV_YCC_601:
		return "xvYCC 601";
	case HDMI_EXTENDED_COLORIMETRY_XV_YCC_709:
		return "xvYCC 709";
	case HDMI_EXTENDED_COLORIMETRY_S_YCC_601:
		return "sYCC 601";
	case HDMI_EXTENDED_COLORIMETRY_OPYCC_601:
		return "opYCC 601";
	case HDMI_EXTENDED_COLORIMETRY_OPRGB:
		return "opRGB";
	case HDMI_EXTENDED_COLORIMETRY_BT2020_CONST_LUM:
		return "BT.2020 Constant Luminance";
	case HDMI_EXTENDED_COLORIMETRY_BT2020:
		return "BT.2020";
	case HDMI_EXTENDED_COLORIMETRY_RESERVED:
		return "Reserved";
	}
	return "Invalid";
}