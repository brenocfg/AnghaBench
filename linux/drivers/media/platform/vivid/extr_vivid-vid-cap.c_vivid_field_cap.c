#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vivid_dev {size_t input; TYPE_2__* dv_timings_cap; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_3__ {scalar_t__ interlaced; } ;
struct TYPE_4__ {TYPE_1__ bt; } ;

/* Variables and functions */
#define  V4L2_FIELD_ALTERNATE 135 
#define  V4L2_FIELD_BOTTOM 134 
#define  V4L2_FIELD_INTERLACED 133 
#define  V4L2_FIELD_INTERLACED_BT 132 
#define  V4L2_FIELD_INTERLACED_TB 131 
 int V4L2_FIELD_NONE ; 
#define  V4L2_FIELD_SEQ_BT 130 
#define  V4L2_FIELD_SEQ_TB 129 
#define  V4L2_FIELD_TOP 128 
 scalar_t__ vivid_is_hdmi_cap (struct vivid_dev*) ; 
 scalar_t__ vivid_is_sdtv_cap (struct vivid_dev*) ; 

__attribute__((used)) static enum v4l2_field vivid_field_cap(struct vivid_dev *dev, enum v4l2_field field)
{
	if (vivid_is_sdtv_cap(dev)) {
		switch (field) {
		case V4L2_FIELD_INTERLACED_TB:
		case V4L2_FIELD_INTERLACED_BT:
		case V4L2_FIELD_SEQ_TB:
		case V4L2_FIELD_SEQ_BT:
		case V4L2_FIELD_TOP:
		case V4L2_FIELD_BOTTOM:
		case V4L2_FIELD_ALTERNATE:
			return field;
		case V4L2_FIELD_INTERLACED:
		default:
			return V4L2_FIELD_INTERLACED;
		}
	}
	if (vivid_is_hdmi_cap(dev))
		return dev->dv_timings_cap[dev->input].bt.interlaced ?
			V4L2_FIELD_ALTERNATE : V4L2_FIELD_NONE;
	return V4L2_FIELD_NONE;
}