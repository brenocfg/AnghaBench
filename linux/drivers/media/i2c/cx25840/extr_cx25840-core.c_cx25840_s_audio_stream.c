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
struct i2c_client {int dummy; } ;
struct cx25840_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx25840_debug ; 
 int cx25840_read (struct i2c_client*,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 scalar_t__ is_cx231xx (struct cx25840_state*) ; 
 scalar_t__ is_cx2388x (struct cx25840_state*) ; 
 scalar_t__ is_cx2583x (struct cx25840_state*) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,char*) ; 

__attribute__((used)) static int cx25840_s_audio_stream(struct v4l2_subdev *sd, int enable)
{
	struct cx25840_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	u8 v;

	if (is_cx2583x(state) || is_cx2388x(state) || is_cx231xx(state))
		return 0;

	v4l_dbg(1, cx25840_debug, client, "%s audio output\n",
		enable ? "enable" : "disable");

	if (enable) {
		v = cx25840_read(client, 0x115) | 0x80;
		cx25840_write(client, 0x115, v);
		v = cx25840_read(client, 0x116) | 0x03;
		cx25840_write(client, 0x116, v);
	} else {
		v = cx25840_read(client, 0x115) & ~(0x80);
		cx25840_write(client, 0x115, v);
		v = cx25840_read(client, 0x116) & ~(0x03);
		cx25840_write(client, 0x116, v);
	}
	return 0;
}