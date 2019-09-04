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
struct TYPE_2__ {int dongle_type; } ;
struct dc_link {TYPE_1__ dpcd_caps; } ;
typedef  enum display_dongle_type { ____Placeholder_display_dongle_type } display_dongle_type ;

/* Variables and functions */
 int DISPLAY_DONGLE_DP_DVI_CONVERTER ; 
 int DISPLAY_DONGLE_DP_HDMI_CONVERTER ; 
 int DISPLAY_DONGLE_DP_VGA_CONVERTER ; 

bool is_dp_active_dongle(const struct dc_link *link)
{
	enum display_dongle_type dongle_type = link->dpcd_caps.dongle_type;

	return (dongle_type == DISPLAY_DONGLE_DP_VGA_CONVERTER) ||
			(dongle_type == DISPLAY_DONGLE_DP_DVI_CONVERTER) ||
			(dongle_type == DISPLAY_DONGLE_DP_HDMI_CONVERTER);
}