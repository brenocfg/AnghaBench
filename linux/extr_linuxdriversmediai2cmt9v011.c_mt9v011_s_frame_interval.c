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
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_fract {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct v4l2_subdev_frame_interval {struct v4l2_fract interval; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R0A_MT9V011_CLK_SPEED ; 
 int /*<<< orphan*/  calc_fps (struct v4l2_subdev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  calc_speed (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  mt9v011_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9v011_s_frame_interval(struct v4l2_subdev *sd,
				    struct v4l2_subdev_frame_interval *ival)
{
	struct v4l2_fract *tpf = &ival->interval;
	u16 speed;

	speed = calc_speed(sd, tpf->numerator, tpf->denominator);

	mt9v011_write(sd, R0A_MT9V011_CLK_SPEED, speed);
	v4l2_dbg(1, debug, sd, "Setting speed to %d\n", speed);

	/* Recalculate and update fps info */
	calc_fps(sd, &tpf->numerator, &tpf->denominator);

	return 0;
}