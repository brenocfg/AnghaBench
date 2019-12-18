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
typedef  enum hdmi_picture_aspect { ____Placeholder_hdmi_picture_aspect } hdmi_picture_aspect ;

/* Variables and functions */
#define  HDMI_PICTURE_ASPECT_16_9 133 
#define  HDMI_PICTURE_ASPECT_256_135 132 
#define  HDMI_PICTURE_ASPECT_4_3 131 
#define  HDMI_PICTURE_ASPECT_64_27 130 
#define  HDMI_PICTURE_ASPECT_NONE 129 
#define  HDMI_PICTURE_ASPECT_RESERVED 128 

__attribute__((used)) static const char *
hdmi_picture_aspect_get_name(enum hdmi_picture_aspect picture_aspect)
{
	switch (picture_aspect) {
	case HDMI_PICTURE_ASPECT_NONE:
		return "No Data";
	case HDMI_PICTURE_ASPECT_4_3:
		return "4:3";
	case HDMI_PICTURE_ASPECT_16_9:
		return "16:9";
	case HDMI_PICTURE_ASPECT_64_27:
		return "64:27";
	case HDMI_PICTURE_ASPECT_256_135:
		return "256:135";
	case HDMI_PICTURE_ASPECT_RESERVED:
		return "Reserved";
	}
	return "Invalid";
}