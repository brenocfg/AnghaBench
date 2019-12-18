#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_8__ {scalar_t__ width; scalar_t__ height; } ;
struct vivid_dev {scalar_t__ field_cap; scalar_t__ field_out; int* std_cap; size_t input; int std_out; TYPE_3__* fmt_out; TYPE_2__* fmt_cap; TYPE_1__ sink_rect; TYPE_4__ src_rect; } ;
struct TYPE_7__ {scalar_t__ fourcc; } ;
struct TYPE_6__ {scalar_t__ fourcc; } ;

/* Variables and functions */
 scalar_t__ V4L2_FIELD_SEQ_BT ; 
 scalar_t__ V4L2_FIELD_SEQ_TB ; 
 int V4L2_STD_525_60 ; 
 scalar_t__ vivid_is_hdmi_cap (struct vivid_dev*) ; 
 scalar_t__ vivid_is_hdmi_out (struct vivid_dev*) ; 
 scalar_t__ vivid_is_svid_cap (struct vivid_dev*) ; 
 scalar_t__ vivid_is_svid_out (struct vivid_dev*) ; 

bool vivid_vid_can_loop(struct vivid_dev *dev)
{
	if (dev->src_rect.width != dev->sink_rect.width ||
	    dev->src_rect.height != dev->sink_rect.height)
		return false;
	if (dev->fmt_cap->fourcc != dev->fmt_out->fourcc)
		return false;
	if (dev->field_cap != dev->field_out)
		return false;
	/*
	 * While this can be supported, it is just too much work
	 * to actually implement.
	 */
	if (dev->field_cap == V4L2_FIELD_SEQ_TB ||
	    dev->field_cap == V4L2_FIELD_SEQ_BT)
		return false;
	if (vivid_is_svid_cap(dev) && vivid_is_svid_out(dev)) {
		if (!(dev->std_cap[dev->input] & V4L2_STD_525_60) !=
		    !(dev->std_out & V4L2_STD_525_60))
			return false;
		return true;
	}
	if (vivid_is_hdmi_cap(dev) && vivid_is_hdmi_out(dev))
		return true;
	return false;
}