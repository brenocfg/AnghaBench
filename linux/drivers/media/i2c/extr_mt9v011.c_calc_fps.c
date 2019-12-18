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
typedef  unsigned int u64 ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct mt9v011 {long xtal; } ;

/* Variables and functions */
 int /*<<< orphan*/  R03_MT9V011_HEIGHT ; 
 int /*<<< orphan*/  R04_MT9V011_WIDTH ; 
 int /*<<< orphan*/  R05_MT9V011_HBLANK ; 
 int /*<<< orphan*/  R06_MT9V011_VBLANK ; 
 int /*<<< orphan*/  R0A_MT9V011_CLK_SPEED ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  do_div (unsigned int,unsigned int) ; 
 unsigned int mt9v011_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct mt9v011* to_mt9v011 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void calc_fps(struct v4l2_subdev *sd, u32 *numerator, u32 *denominator)
{
	struct mt9v011 *core = to_mt9v011(sd);
	unsigned height, width, hblank, vblank, speed;
	unsigned row_time, t_time;
	u64 frames_per_ms;
	unsigned tmp;

	height = mt9v011_read(sd, R03_MT9V011_HEIGHT);
	width = mt9v011_read(sd, R04_MT9V011_WIDTH);
	hblank = mt9v011_read(sd, R05_MT9V011_HBLANK);
	vblank = mt9v011_read(sd, R06_MT9V011_VBLANK);
	speed = mt9v011_read(sd, R0A_MT9V011_CLK_SPEED);

	row_time = (width + 113 + hblank) * (speed + 2);
	t_time = row_time * (height + vblank + 1);

	frames_per_ms = core->xtal * 1000l;
	do_div(frames_per_ms, t_time);
	tmp = frames_per_ms;

	v4l2_dbg(1, debug, sd, "Programmed to %u.%03u fps (%d pixel clcks)\n",
		tmp / 1000, tmp % 1000, t_time);

	if (numerator && denominator) {
		*numerator = 1000;
		*denominator = (u32)frames_per_ms;
	}
}