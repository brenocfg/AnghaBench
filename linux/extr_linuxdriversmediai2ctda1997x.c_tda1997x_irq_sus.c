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
struct tda1997x_state {struct v4l2_subdev sd; int /*<<< orphan*/  client; scalar_t__ hdmi_status; scalar_t__ mptrw_in_progress; } ;

/* Variables and functions */
 int LAST_STATE_REACHED ; 
 int MASK_FMT ; 
 int MASK_MPT ; 
 int MASK_SR_FIFO_FIFO_CTRL ; 
 int MASK_SUS_END ; 
 int MASK_SUS_STATUS ; 
 int /*<<< orphan*/  REG_HDMI_INFO_RST ; 
 int /*<<< orphan*/  REG_INT_FLG_CLR_SUS ; 
 int /*<<< orphan*/  REG_SUS_STATUS ; 
 scalar_t__ debug ; 
 int io_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tda1997x_detect_std (struct tda1997x_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tda1997x_ev_fmt ; 
 int /*<<< orphan*/  v4l2_subdev_notify_event (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void tda1997x_irq_sus(struct tda1997x_state *state, u8 *flags)
{
	struct v4l2_subdev *sd = &state->sd;
	u8 reg, source;

	source = io_read(sd, REG_INT_FLG_CLR_SUS);
	io_write(sd, REG_INT_FLG_CLR_SUS, source);

	if (source & MASK_MPT) {
		/* reset MTP in use flag if set */
		if (state->mptrw_in_progress)
			state->mptrw_in_progress = 0;
	}

	if (source & MASK_SUS_END) {
		/* reset audio FIFO */
		reg = io_read(sd, REG_HDMI_INFO_RST);
		reg |= MASK_SR_FIFO_FIFO_CTRL;
		io_write(sd, REG_HDMI_INFO_RST, reg);
		reg &= ~MASK_SR_FIFO_FIFO_CTRL;
		io_write(sd, REG_HDMI_INFO_RST, reg);

		/* reset HDMI flags */
		state->hdmi_status = 0;
	}

	/* filter FMT interrupt based on SUS state */
	reg = io_read(sd, REG_SUS_STATUS);
	if (((reg & MASK_SUS_STATUS) != LAST_STATE_REACHED)
	   || (source & MASK_MPT)) {
		source &= ~MASK_FMT;
	}

	if (source & (MASK_FMT | MASK_SUS_END)) {
		reg = io_read(sd, REG_SUS_STATUS);
		if ((reg & MASK_SUS_STATUS) != LAST_STATE_REACHED) {
			v4l_err(state->client, "BAD SUS STATUS\n");
			return;
		}
		if (debug)
			tda1997x_detect_std(state, NULL);
		/* notify user of change in resolution */
		v4l2_subdev_notify_event(&state->sd, &tda1997x_ev_fmt);
	}
}