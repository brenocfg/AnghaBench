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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct ov5647 {int flags; } ;

/* Variables and functions */
 int MIPI_CTRL00_BUS_IDLE ; 
 int MIPI_CTRL00_CLOCK_LANE_GATE ; 
 int MIPI_CTRL00_LINE_SYNC_ENABLE ; 
 int /*<<< orphan*/  OV5640_REG_PAD_OUT ; 
 int /*<<< orphan*/  OV5647_REG_FRAME_OFF_NUMBER ; 
 int /*<<< orphan*/  OV5647_REG_MIPI_CTRL00 ; 
 int V4L2_MBUS_CSI2_NONCONTINUOUS_CLOCK ; 
 int ov5647_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct ov5647* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov5647_stream_on(struct v4l2_subdev *sd)
{
	struct ov5647 *ov5647 = to_state(sd);
	u8 val = MIPI_CTRL00_BUS_IDLE;
	int ret;

	if (ov5647->flags & V4L2_MBUS_CSI2_NONCONTINUOUS_CLOCK)
		val |= MIPI_CTRL00_CLOCK_LANE_GATE |
		       MIPI_CTRL00_LINE_SYNC_ENABLE;

	ret = ov5647_write(sd, OV5647_REG_MIPI_CTRL00, val);
	if (ret < 0)
		return ret;

	ret = ov5647_write(sd, OV5647_REG_FRAME_OFF_NUMBER, 0x00);
	if (ret < 0)
		return ret;

	return ov5647_write(sd, OV5640_REG_PAD_OUT, 0x00);
}