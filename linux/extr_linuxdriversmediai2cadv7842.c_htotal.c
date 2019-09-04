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
struct v4l2_bt_timings {int dummy; } ;

/* Variables and functions */
 int V4L2_DV_BT_FRAME_WIDTH (struct v4l2_bt_timings const*) ; 

__attribute__((used)) static inline unsigned htotal(const struct v4l2_bt_timings *t)
{
	return V4L2_DV_BT_FRAME_WIDTH(t);
}