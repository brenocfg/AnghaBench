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
struct v4l2_sliced_vbi_data {int line; scalar_t__ field; int* data; } ;
struct saa7127_state {int wss_enable; int wss_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  saa7127_write (struct v4l2_subdev*,int,int) ; 
 struct saa7127_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,char*) ; 
 char** wss_strs ; 

__attribute__((used)) static int saa7127_set_wss(struct v4l2_subdev *sd, const struct v4l2_sliced_vbi_data *data)
{
	struct saa7127_state *state = to_state(sd);
	int enable = (data->line != 0);

	if (enable && (data->field != 0 || data->line != 23))
		return -EINVAL;
	if (state->wss_enable != enable) {
		v4l2_dbg(1, debug, sd, "Turn WSS %s\n", enable ? "on" : "off");
		saa7127_write(sd, 0x27, enable << 7);
		state->wss_enable = enable;
	}
	if (!enable)
		return 0;

	saa7127_write(sd, 0x26, data->data[0]);
	saa7127_write(sd, 0x27, 0x80 | (data->data[1] & 0x3f));
	v4l2_dbg(1, debug, sd,
		"WSS mode: %s\n", wss_strs[data->data[0] & 0xf]);
	state->wss_mode = (data->data[1] & 0x3f) << 8 | data->data[0];
	return 0;
}