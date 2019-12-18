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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_sliced_vbi_data {int* data; int line; scalar_t__ field; } ;
struct saa7127_state {int cc_enable; int xds_enable; int cc_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SAA7127_REG_CLOSED_CAPTION ; 
 int /*<<< orphan*/  SAA7127_REG_LINE_21_ODD_0 ; 
 int /*<<< orphan*/  SAA7127_REG_LINE_21_ODD_1 ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  saa7127_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct saa7127_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,...) ; 

__attribute__((used)) static int saa7127_set_cc(struct v4l2_subdev *sd, const struct v4l2_sliced_vbi_data *data)
{
	struct saa7127_state *state = to_state(sd);
	u16 cc = data->data[1] << 8 | data->data[0];
	int enable = (data->line != 0);

	if (enable && (data->field != 0 || data->line != 21))
		return -EINVAL;
	if (state->cc_enable != enable) {
		v4l2_dbg(1, debug, sd,
			"Turn CC %s\n", enable ? "on" : "off");
		saa7127_write(sd, SAA7127_REG_CLOSED_CAPTION,
			(state->xds_enable << 7) | (enable << 6) | 0x11);
		state->cc_enable = enable;
	}
	if (!enable)
		return 0;

	v4l2_dbg(2, debug, sd, "CC data: %04x\n", cc);
	saa7127_write(sd, SAA7127_REG_LINE_21_ODD_0, cc & 0xff);
	saa7127_write(sd, SAA7127_REG_LINE_21_ODD_1, cc >> 8);
	state->cc_data = cc;
	return 0;
}