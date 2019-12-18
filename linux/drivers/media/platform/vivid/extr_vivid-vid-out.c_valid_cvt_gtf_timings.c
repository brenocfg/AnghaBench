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
struct v4l2_bt_timings {int standards; } ;
struct v4l2_dv_timings {struct v4l2_bt_timings bt; } ;

/* Variables and functions */
 int V4L2_DV_BT_STD_CVT ; 
 int V4L2_DV_BT_STD_GTF ; 
 scalar_t__ v4l2_valid_dv_timings (struct v4l2_dv_timings*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vivid_dv_timings_cap ; 

__attribute__((used)) static bool valid_cvt_gtf_timings(struct v4l2_dv_timings *timings)
{
	struct v4l2_bt_timings *bt = &timings->bt;

	if ((bt->standards & (V4L2_DV_BT_STD_CVT | V4L2_DV_BT_STD_GTF)) &&
	    v4l2_valid_dv_timings(timings, &vivid_dv_timings_cap, NULL, NULL))
		return true;

	return false;
}