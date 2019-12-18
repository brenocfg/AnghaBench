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
struct vivid_dev {int* std_aspect_ratio; size_t input; int* dv_timings_aspect_ratio; } ;
typedef  enum tpg_video_aspect { ____Placeholder_tpg_video_aspect } tpg_video_aspect ;

/* Variables and functions */
 int TPG_VIDEO_ASPECT_IMAGE ; 
 scalar_t__ vivid_is_hdmi_cap (struct vivid_dev const*) ; 
 scalar_t__ vivid_is_sdtv_cap (struct vivid_dev const*) ; 

enum tpg_video_aspect vivid_get_video_aspect(const struct vivid_dev *dev)
{
	if (vivid_is_sdtv_cap(dev))
		return dev->std_aspect_ratio[dev->input];

	if (vivid_is_hdmi_cap(dev))
		return dev->dv_timings_aspect_ratio[dev->input];

	return TPG_VIDEO_ASPECT_IMAGE;
}