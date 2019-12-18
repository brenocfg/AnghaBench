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
typedef  int v4l2_std_id ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ left; scalar_t__ top; } ;

/* Variables and functions */
 int /*<<< orphan*/  TVP5150_H_MAX ; 
 int /*<<< orphan*/  TVP5150_V_MAX_525_60 ; 
 int /*<<< orphan*/  TVP5150_V_MAX_OTHERS ; 
 int V4L2_STD_525_60 ; 

__attribute__((used)) static void tvp5150_set_default(v4l2_std_id std, struct v4l2_rect *crop)
{
	/* Default is no cropping */
	crop->top = 0;
	crop->left = 0;
	crop->width = TVP5150_H_MAX;
	if (std & V4L2_STD_525_60)
		crop->height = TVP5150_V_MAX_525_60;
	else
		crop->height = TVP5150_V_MAX_OTHERS;
}