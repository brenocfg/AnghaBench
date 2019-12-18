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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_IN_ST_NO_SIGNAL ; 
 int cx25840_read4 (struct i2c_client*,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx25840_g_input_status(struct v4l2_subdev *sd, u32 *status)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	/*
	 * A limited function that checks for signal status and returns
	 * the state.
	 */

	/* Check for status of Horizontal lock (SRC lock isn't reliable) */
	if ((cx25840_read4(client, 0x40c) & 0x00010000) == 0)
		*status |= V4L2_IN_ST_NO_SIGNAL;

	return 0;
}