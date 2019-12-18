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
struct v4l2_subdev {int dummy; } ;
struct v4l2_fract {int numerator; int denominator; } ;

/* Variables and functions */

__attribute__((used)) static int adv748x_hdmi_g_pixelaspect(struct v4l2_subdev *sd,
				      struct v4l2_fract *aspect)
{
	aspect->numerator = 1;
	aspect->denominator = 1;

	return 0;
}