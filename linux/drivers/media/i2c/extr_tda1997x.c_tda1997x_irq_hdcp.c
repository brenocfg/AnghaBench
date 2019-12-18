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
struct tda1997x_state {scalar_t__ mptrw_in_progress; struct v4l2_subdev sd; } ;

/* Variables and functions */
 int INTERRUPT_AUDIO ; 
 int INTERRUPT_INFO ; 
 int MASK_HDCP_MTP ; 
 int MASK_STATE_C5 ; 
 int /*<<< orphan*/  REG_INT_FLG_CLR_HDCP ; 
 int /*<<< orphan*/  REG_INT_MASK_TOP ; 
 int io_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tda1997x_irq_hdcp(struct tda1997x_state *state, u8 *flags)
{
	struct v4l2_subdev *sd = &state->sd;
	u8 reg, source;

	source = io_read(sd, REG_INT_FLG_CLR_HDCP);
	io_write(sd, REG_INT_FLG_CLR_HDCP, source);

	/* reset MTP in use flag if set */
	if (source & MASK_HDCP_MTP)
		state->mptrw_in_progress = 0;
	if (source & MASK_STATE_C5) {
		/* REPEATER: mask AUDIO and IF irqs to avoid IF during auth */
		reg = io_read(sd, REG_INT_MASK_TOP);
		reg &= ~(INTERRUPT_AUDIO | INTERRUPT_INFO);
		io_write(sd, REG_INT_MASK_TOP, reg);
		*flags &= (INTERRUPT_AUDIO | INTERRUPT_INFO);
	}
}