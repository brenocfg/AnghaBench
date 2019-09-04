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
struct tvp7002 {int streaming; } ;

/* Variables and functions */
 int /*<<< orphan*/  TVP7002_MISC_CTL_2 ; 
 int /*<<< orphan*/  debug ; 
 struct tvp7002* to_tvp7002 (struct v4l2_subdev*) ; 
 int tvp7002_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int tvp7002_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct tvp7002 *device = to_tvp7002(sd);
	int error;

	if (device->streaming == enable)
		return 0;

	/* low impedance: on, high impedance: off */
	error = tvp7002_write(sd, TVP7002_MISC_CTL_2, enable ? 0x00 : 0x03);
	if (error) {
		v4l2_dbg(1, debug, sd, "Fail to set streaming\n");
		return error;
	}

	device->streaming = enable;
	return 0;
}