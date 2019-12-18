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
typedef  enum hdmi_colorimetry { ____Placeholder_hdmi_colorimetry } hdmi_colorimetry ;

/* Variables and functions */
#define  HDMI_COLORIMETRY_EXTENDED 131 
#define  HDMI_COLORIMETRY_ITU_601 130 
#define  HDMI_COLORIMETRY_ITU_709 129 
#define  HDMI_COLORIMETRY_NONE 128 

__attribute__((used)) static const char *hdmi_colorimetry_get_name(enum hdmi_colorimetry colorimetry)
{
	switch (colorimetry) {
	case HDMI_COLORIMETRY_NONE:
		return "No Data";
	case HDMI_COLORIMETRY_ITU_601:
		return "ITU601";
	case HDMI_COLORIMETRY_ITU_709:
		return "ITU709";
	case HDMI_COLORIMETRY_EXTENDED:
		return "Extended";
	}
	return "Invalid";
}