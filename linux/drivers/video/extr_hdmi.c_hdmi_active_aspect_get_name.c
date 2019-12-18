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
typedef  enum hdmi_active_aspect { ____Placeholder_hdmi_active_aspect } hdmi_active_aspect ;

/* Variables and functions */
#define  HDMI_ACTIVE_ASPECT_14_9 137 
#define  HDMI_ACTIVE_ASPECT_14_9_TOP 136 
#define  HDMI_ACTIVE_ASPECT_16_9 135 
#define  HDMI_ACTIVE_ASPECT_16_9_CENTER 134 
#define  HDMI_ACTIVE_ASPECT_16_9_SP_14_9 133 
#define  HDMI_ACTIVE_ASPECT_16_9_SP_4_3 132 
#define  HDMI_ACTIVE_ASPECT_16_9_TOP 131 
#define  HDMI_ACTIVE_ASPECT_4_3 130 
#define  HDMI_ACTIVE_ASPECT_4_3_SP_14_9 129 
#define  HDMI_ACTIVE_ASPECT_PICTURE 128 

__attribute__((used)) static const char *
hdmi_active_aspect_get_name(enum hdmi_active_aspect active_aspect)
{
	if (active_aspect < 0 || active_aspect > 0xf)
		return "Invalid";

	switch (active_aspect) {
	case HDMI_ACTIVE_ASPECT_16_9_TOP:
		return "16:9 Top";
	case HDMI_ACTIVE_ASPECT_14_9_TOP:
		return "14:9 Top";
	case HDMI_ACTIVE_ASPECT_16_9_CENTER:
		return "16:9 Center";
	case HDMI_ACTIVE_ASPECT_PICTURE:
		return "Same as Picture";
	case HDMI_ACTIVE_ASPECT_4_3:
		return "4:3";
	case HDMI_ACTIVE_ASPECT_16_9:
		return "16:9";
	case HDMI_ACTIVE_ASPECT_14_9:
		return "14:9";
	case HDMI_ACTIVE_ASPECT_4_3_SP_14_9:
		return "4:3 SP 14:9";
	case HDMI_ACTIVE_ASPECT_16_9_SP_14_9:
		return "16:9 SP 14:9";
	case HDMI_ACTIVE_ASPECT_16_9_SP_4_3:
		return "16:9 SP 4:3";
	}
	return "Reserved";
}