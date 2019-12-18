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
typedef  scalar_t__ (* v4l2_check_dv_timings_fnc ) (struct v4l2_dv_timings const*,void*) ;
typedef  int u32 ;
struct v4l2_bt_timings_cap {int capabilities; scalar_t__ min_height; scalar_t__ max_height; scalar_t__ min_width; scalar_t__ max_width; scalar_t__ min_pixelclock; scalar_t__ max_pixelclock; int standards; } ;
struct v4l2_dv_timings_cap {scalar_t__ type; struct v4l2_bt_timings_cap bt; } ;
struct v4l2_bt_timings {scalar_t__ height; scalar_t__ width; scalar_t__ pixelclock; int standards; scalar_t__ interlaced; } ;
struct v4l2_dv_timings {scalar_t__ type; struct v4l2_bt_timings bt; } ;

/* Variables and functions */
 scalar_t__ V4L2_DV_BT_656_1120 ; 
 int V4L2_DV_BT_CAP_CUSTOM ; 
 int V4L2_DV_BT_CAP_INTERLACED ; 
 int V4L2_DV_BT_CAP_PROGRESSIVE ; 

bool v4l2_valid_dv_timings(const struct v4l2_dv_timings *t,
			   const struct v4l2_dv_timings_cap *dvcap,
			   v4l2_check_dv_timings_fnc fnc,
			   void *fnc_handle)
{
	const struct v4l2_bt_timings *bt = &t->bt;
	const struct v4l2_bt_timings_cap *cap = &dvcap->bt;
	u32 caps = cap->capabilities;

	if (t->type != V4L2_DV_BT_656_1120)
		return false;
	if (t->type != dvcap->type ||
	    bt->height < cap->min_height ||
	    bt->height > cap->max_height ||
	    bt->width < cap->min_width ||
	    bt->width > cap->max_width ||
	    bt->pixelclock < cap->min_pixelclock ||
	    bt->pixelclock > cap->max_pixelclock ||
	    (!(caps & V4L2_DV_BT_CAP_CUSTOM) &&
	     cap->standards && bt->standards &&
	     !(bt->standards & cap->standards)) ||
	    (bt->interlaced && !(caps & V4L2_DV_BT_CAP_INTERLACED)) ||
	    (!bt->interlaced && !(caps & V4L2_DV_BT_CAP_PROGRESSIVE)))
		return false;
	return fnc == NULL || fnc(t, fnc_handle);
}