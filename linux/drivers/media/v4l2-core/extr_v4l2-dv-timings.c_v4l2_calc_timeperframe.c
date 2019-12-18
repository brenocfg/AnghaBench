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
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct v4l2_fract {int member_0; int member_1; unsigned long numerator; unsigned long denominator; } ;
struct v4l2_bt_timings {unsigned long long pixelclock; int flags; } ;
struct v4l2_dv_timings {scalar_t__ type; struct v4l2_bt_timings bt; } ;

/* Variables and functions */
 scalar_t__ V4L2_DV_BT_656_1120 ; 
 int V4L2_DV_BT_FRAME_HEIGHT (struct v4l2_bt_timings const*) ; 
 int V4L2_DV_BT_FRAME_WIDTH (struct v4l2_bt_timings const*) ; 
 int V4L2_DV_FL_CAN_DETECT_REDUCED_FPS ; 
 int V4L2_DV_FL_REDUCED_FPS ; 
 void* div_u64 (int,int) ; 
 int /*<<< orphan*/  rational_best_approximation (int,int,int,int,unsigned long*,unsigned long*) ; 

struct v4l2_fract v4l2_calc_timeperframe(const struct v4l2_dv_timings *t)
{
	const struct v4l2_bt_timings *bt = &t->bt;
	struct v4l2_fract fps_fract = { 1, 1 };
	unsigned long n, d;
	u32 htot, vtot, fps;
	u64 pclk;

	if (t->type != V4L2_DV_BT_656_1120)
		return fps_fract;

	htot = V4L2_DV_BT_FRAME_WIDTH(bt);
	vtot = V4L2_DV_BT_FRAME_HEIGHT(bt);
	pclk = bt->pixelclock;

	if ((bt->flags & V4L2_DV_FL_CAN_DETECT_REDUCED_FPS) &&
	    (bt->flags & V4L2_DV_FL_REDUCED_FPS))
		pclk = div_u64(pclk * 1000ULL, 1001);

	fps = (htot * vtot) > 0 ? div_u64((100 * pclk), (htot * vtot)) : 0;
	if (!fps)
		return fps_fract;

	rational_best_approximation(fps, 100, fps, 100, &n, &d);

	fps_fract.numerator = d;
	fps_fract.denominator = n;
	return fps_fract;
}