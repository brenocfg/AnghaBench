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
struct v4l2_vbi_format {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int std; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  cx25840_std_setup (struct i2c_client*) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 scalar_t__ is_cx23888 (struct cx25840_state*) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

int cx25840_s_raw_fmt(struct v4l2_subdev *sd, struct v4l2_vbi_format *fmt)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct cx25840_state *state = to_state(sd);
	int is_pal = !(state->std & V4L2_STD_525_60);
	int vbi_offset = is_pal ? 1 : 0;

	/* Setup standard */
	cx25840_std_setup(client);

	/* VBI Offset */
	if (is_cx23888(state))
		cx25840_write(client, 0x54f, vbi_offset);
	else
		cx25840_write(client, 0x47f, vbi_offset);
	/* TODO: this will have to be changed for generic_mode VBI */
	cx25840_write(client, 0x404, 0x2e);
	return 0;
}