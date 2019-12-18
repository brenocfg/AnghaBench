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
typedef  enum hdmi_scan_mode { ____Placeholder_hdmi_scan_mode } hdmi_scan_mode ;

/* Variables and functions */
#define  HDMI_SCAN_MODE_NONE 131 
#define  HDMI_SCAN_MODE_OVERSCAN 130 
#define  HDMI_SCAN_MODE_RESERVED 129 
#define  HDMI_SCAN_MODE_UNDERSCAN 128 

__attribute__((used)) static const char *hdmi_scan_mode_get_name(enum hdmi_scan_mode scan_mode)
{
	switch (scan_mode) {
	case HDMI_SCAN_MODE_NONE:
		return "No Data";
	case HDMI_SCAN_MODE_OVERSCAN:
		return "Overscan";
	case HDMI_SCAN_MODE_UNDERSCAN:
		return "Underscan";
	case HDMI_SCAN_MODE_RESERVED:
		return "Reserved";
	}
	return "Invalid";
}