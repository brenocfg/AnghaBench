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
struct TYPE_2__ {scalar_t__ width; scalar_t__ height; scalar_t__ interlaced; scalar_t__ polarities; unsigned int pixelclock; scalar_t__ hfrontporch; scalar_t__ hsync; scalar_t__ hbackporch; scalar_t__ vfrontporch; scalar_t__ vsync; scalar_t__ vbackporch; int flags; scalar_t__ il_vfrontporch; scalar_t__ il_vsync; scalar_t__ il_vbackporch; } ;
struct v4l2_dv_timings {scalar_t__ type; TYPE_1__ bt; } ;

/* Variables and functions */
 scalar_t__ V4L2_DV_BT_656_1120 ; 
 int V4L2_DV_FL_REDUCED_FPS ; 

bool v4l2_match_dv_timings(const struct v4l2_dv_timings *t1,
			   const struct v4l2_dv_timings *t2,
			   unsigned pclock_delta, bool match_reduced_fps)
{
	if (t1->type != t2->type || t1->type != V4L2_DV_BT_656_1120)
		return false;
	if (t1->bt.width == t2->bt.width &&
	    t1->bt.height == t2->bt.height &&
	    t1->bt.interlaced == t2->bt.interlaced &&
	    t1->bt.polarities == t2->bt.polarities &&
	    t1->bt.pixelclock >= t2->bt.pixelclock - pclock_delta &&
	    t1->bt.pixelclock <= t2->bt.pixelclock + pclock_delta &&
	    t1->bt.hfrontporch == t2->bt.hfrontporch &&
	    t1->bt.hsync == t2->bt.hsync &&
	    t1->bt.hbackporch == t2->bt.hbackporch &&
	    t1->bt.vfrontporch == t2->bt.vfrontporch &&
	    t1->bt.vsync == t2->bt.vsync &&
	    t1->bt.vbackporch == t2->bt.vbackporch &&
	    (!match_reduced_fps ||
	     (t1->bt.flags & V4L2_DV_FL_REDUCED_FPS) ==
		(t2->bt.flags & V4L2_DV_FL_REDUCED_FPS)) &&
	    (!t1->bt.interlaced ||
		(t1->bt.il_vfrontporch == t2->bt.il_vfrontporch &&
		 t1->bt.il_vsync == t2->bt.il_vsync &&
		 t1->bt.il_vbackporch == t2->bt.il_vbackporch)))
		return true;
	return false;
}