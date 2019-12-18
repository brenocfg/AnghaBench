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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int /*<<< orphan*/  hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx25840_ir_log_status (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  is_cx2583x (struct cx25840_state*) ; 
 int /*<<< orphan*/  log_audio_status (struct i2c_client*) ; 
 int /*<<< orphan*/  log_video_status (struct i2c_client*) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_log_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx25840_log_status(struct v4l2_subdev *sd)
{
	struct cx25840_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	log_video_status(client);
	if (!is_cx2583x(state))
		log_audio_status(client);
	cx25840_ir_log_status(sd);
	v4l2_ctrl_handler_log_status(&state->hdl, sd->name);
	return 0;
}