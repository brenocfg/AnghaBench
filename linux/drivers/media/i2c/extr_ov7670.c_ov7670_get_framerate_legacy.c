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
struct ov7670_info {int clock_speed; int clkrc; } ;

/* Variables and functions */
 int CLK_EXT ; 
 int CLK_SCALE ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static void ov7670_get_framerate_legacy(struct v4l2_subdev *sd,
				 struct v4l2_fract *tpf)
{
	struct ov7670_info *info = to_state(sd);

	tpf->numerator = 1;
	tpf->denominator = info->clock_speed;
	if ((info->clkrc & CLK_EXT) == 0 && (info->clkrc & CLK_SCALE) > 1)
		tpf->denominator /= (info->clkrc & CLK_SCALE);
}