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
struct TYPE_3__ {scalar_t__ interlaced; } ;
struct TYPE_4__ {TYPE_1__ bt; } ;
struct vivid_dev {TYPE_2__ dv_timings_out; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
#define  V4L2_FIELD_ALTERNATE 133 
#define  V4L2_FIELD_INTERLACED 132 
#define  V4L2_FIELD_INTERLACED_BT 131 
#define  V4L2_FIELD_INTERLACED_TB 130 
 int V4L2_FIELD_NONE ; 
#define  V4L2_FIELD_SEQ_BT 129 
#define  V4L2_FIELD_SEQ_TB 128 
 scalar_t__ vivid_is_hdmi_out (struct vivid_dev*) ; 
 scalar_t__ vivid_is_svid_out (struct vivid_dev*) ; 

__attribute__((used)) static enum v4l2_field vivid_field_out(struct vivid_dev *dev, enum v4l2_field field)
{
	if (vivid_is_svid_out(dev)) {
		switch (field) {
		case V4L2_FIELD_INTERLACED_TB:
		case V4L2_FIELD_INTERLACED_BT:
		case V4L2_FIELD_SEQ_TB:
		case V4L2_FIELD_SEQ_BT:
		case V4L2_FIELD_ALTERNATE:
			return field;
		case V4L2_FIELD_INTERLACED:
		default:
			return V4L2_FIELD_INTERLACED;
		}
	}
	if (vivid_is_hdmi_out(dev))
		return dev->dv_timings_out.bt.interlaced ? V4L2_FIELD_ALTERNATE :
						       V4L2_FIELD_NONE;
	return V4L2_FIELD_NONE;
}