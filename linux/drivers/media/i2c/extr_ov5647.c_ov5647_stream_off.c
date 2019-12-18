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

/* Variables and functions */
 int MIPI_CTRL00_BUS_IDLE ; 
 int MIPI_CTRL00_CLOCK_LANE_DISABLE ; 
 int MIPI_CTRL00_CLOCK_LANE_GATE ; 
 int /*<<< orphan*/  OV5640_REG_PAD_OUT ; 
 int /*<<< orphan*/  OV5647_REG_FRAME_OFF_NUMBER ; 
 int /*<<< orphan*/  OV5647_REG_MIPI_CTRL00 ; 
 int ov5647_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov5647_stream_off(struct v4l2_subdev *sd)
{
	int ret;

	ret = ov5647_write(sd, OV5647_REG_MIPI_CTRL00, MIPI_CTRL00_CLOCK_LANE_GATE
			   | MIPI_CTRL00_BUS_IDLE | MIPI_CTRL00_CLOCK_LANE_DISABLE);
	if (ret < 0)
		return ret;

	ret = ov5647_write(sd, OV5647_REG_FRAME_OFF_NUMBER, 0x0f);
	if (ret < 0)
		return ret;

	return ov5647_write(sd, OV5640_REG_PAD_OUT, 0x01);
}