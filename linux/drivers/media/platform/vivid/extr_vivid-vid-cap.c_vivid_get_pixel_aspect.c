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
struct TYPE_2__ {int width; int height; } ;
struct vivid_dev {int* std_cap; size_t input; TYPE_1__ src_rect; } ;
typedef  enum tpg_pixel_aspect { ____Placeholder_tpg_pixel_aspect } tpg_pixel_aspect ;

/* Variables and functions */
 int TPG_PIXEL_ASPECT_NTSC ; 
 int TPG_PIXEL_ASPECT_PAL ; 
 int TPG_PIXEL_ASPECT_SQUARE ; 
 int V4L2_STD_525_60 ; 
 scalar_t__ vivid_is_hdmi_cap (struct vivid_dev const*) ; 
 scalar_t__ vivid_is_sdtv_cap (struct vivid_dev const*) ; 

__attribute__((used)) static enum tpg_pixel_aspect vivid_get_pixel_aspect(const struct vivid_dev *dev)
{
	if (vivid_is_sdtv_cap(dev))
		return (dev->std_cap[dev->input] & V4L2_STD_525_60) ?
			TPG_PIXEL_ASPECT_NTSC : TPG_PIXEL_ASPECT_PAL;

	if (vivid_is_hdmi_cap(dev) &&
	    dev->src_rect.width == 720 && dev->src_rect.height <= 576)
		return dev->src_rect.height == 480 ?
			TPG_PIXEL_ASPECT_NTSC : TPG_PIXEL_ASPECT_PAL;

	return TPG_PIXEL_ASPECT_SQUARE;
}