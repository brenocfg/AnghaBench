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
struct tda1997x_state {int activity_status; scalar_t__ chip_revision; int* input_detect; int /*<<< orphan*/  client; struct v4l2_subdev sd; } ;

/* Variables and functions */
 int MASK_RATE_A_ST ; 
 int MASK_RATE_B_ST ; 
 int PIX_REPEAT_MASK_REP ; 
 int PIX_REPEAT_MASK_UP_SEL ; 
 int /*<<< orphan*/  REG_INT_FLG_CLR_RATE ; 
 int /*<<< orphan*/  REG_PIX_REPEAT ; 
 int io_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tda1997x_ev_fmt ; 
 int tda1997x_read_activity_status_regs (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tda1997x_reset_n1 (struct tda1997x_state*) ; 
 int /*<<< orphan*/  v4l2_subdev_notify_event (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void tda1997x_irq_rate(struct tda1997x_state *state, u8 *flags)
{
	struct v4l2_subdev *sd = &state->sd;
	u8 reg, source;

	u8 irq_status;

	source = io_read(sd, REG_INT_FLG_CLR_RATE);
	io_write(sd, REG_INT_FLG_CLR_RATE, source);

	/* read status regs */
	irq_status = tda1997x_read_activity_status_regs(sd);

	/*
	 * read clock status reg until INT_FLG_CLR_RATE is still 0
	 * after the read to make sure its the last one
	 */
	reg = source;
	while (reg != 0) {
		irq_status = tda1997x_read_activity_status_regs(sd);
		reg = io_read(sd, REG_INT_FLG_CLR_RATE);
		io_write(sd, REG_INT_FLG_CLR_RATE, reg);
		source |= reg;
	}

	/* we only pay attention to stability change events */
	if (source & (MASK_RATE_A_ST | MASK_RATE_B_ST)) {
		int input = (source & MASK_RATE_A_ST)?0:1;
		u8 mask = 1<<input;

		/* state change */
		if ((irq_status & mask) != (state->activity_status & mask)) {
			/* activity lost */
			if ((irq_status & mask) == 0) {
				v4l_info(state->client,
					 "HDMI-%c: Digital Activity Lost\n",
					 input+'A');

				/* bypass up/down sampler and pixel repeater */
				reg = io_read(sd, REG_PIX_REPEAT);
				reg &= ~PIX_REPEAT_MASK_UP_SEL;
				reg &= ~PIX_REPEAT_MASK_REP;
				io_write(sd, REG_PIX_REPEAT, reg);

				if (state->chip_revision == 0)
					tda1997x_reset_n1(state);

				state->input_detect[input] = 0;
				v4l2_subdev_notify_event(sd, &tda1997x_ev_fmt);
			}

			/* activity detected */
			else {
				v4l_info(state->client,
					 "HDMI-%c: Digital Activity Detected\n",
					 input+'A');
				state->input_detect[input] = 1;
			}

			/* hold onto current state */
			state->activity_status = (irq_status & mask);
		}
	}
}