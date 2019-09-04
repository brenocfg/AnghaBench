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
struct v4l2_frequency {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wm8775_set_audio (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8775_s_frequency(struct v4l2_subdev *sd, const struct v4l2_frequency *freq)
{
	wm8775_set_audio(sd, 0);
	return 0;
}