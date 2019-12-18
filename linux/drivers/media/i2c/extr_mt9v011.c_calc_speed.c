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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct mt9v011 {int xtal; } ;

/* Variables and functions */
 int /*<<< orphan*/  R03_MT9V011_HEIGHT ; 
 int /*<<< orphan*/  R04_MT9V011_WIDTH ; 
 int /*<<< orphan*/  R05_MT9V011_HBLANK ; 
 int /*<<< orphan*/  R06_MT9V011_VBLANK ; 
 int /*<<< orphan*/  do_div (int,unsigned int) ; 
 unsigned int mt9v011_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct mt9v011* to_mt9v011 (struct v4l2_subdev*) ; 

__attribute__((used)) static u16 calc_speed(struct v4l2_subdev *sd, u32 numerator, u32 denominator)
{
	struct mt9v011 *core = to_mt9v011(sd);
	unsigned height, width, hblank, vblank;
	unsigned row_time, line_time;
	u64 t_time, speed;

	/* Avoid bogus calculus */
	if (!numerator || !denominator)
		return 0;

	height = mt9v011_read(sd, R03_MT9V011_HEIGHT);
	width = mt9v011_read(sd, R04_MT9V011_WIDTH);
	hblank = mt9v011_read(sd, R05_MT9V011_HBLANK);
	vblank = mt9v011_read(sd, R06_MT9V011_VBLANK);

	row_time = width + 113 + hblank;
	line_time = height + vblank + 1;

	t_time = core->xtal * ((u64)numerator);
	/* round to the closest value */
	t_time += denominator / 2;
	do_div(t_time, denominator);

	speed = t_time;
	do_div(speed, row_time * line_time);

	/* Avoid having a negative value for speed */
	if (speed < 2)
		speed = 0;
	else
		speed -= 2;

	/* Avoid speed overflow */
	if (speed > 15)
		return 15;

	return (u16)speed;
}