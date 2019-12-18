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
typedef  size_t u8 ;
typedef  enum hdmi_picture_aspect { ____Placeholder_hdmi_picture_aspect } hdmi_picture_aspect ;
struct TYPE_2__ {int picture_aspect_ratio; } ;

/* Variables and functions */
 TYPE_1__* edid_cea_modes ; 

enum hdmi_picture_aspect drm_get_cea_aspect_ratio(const u8 video_code)
{
	return edid_cea_modes[video_code].picture_aspect_ratio;
}