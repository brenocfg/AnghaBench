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
struct tda1997x_state {int /*<<< orphan*/  lock; struct v4l2_subdev sd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int INTERRUPT_AUDIO ; 
 int INTERRUPT_DDC ; 
 int INTERRUPT_HDCP ; 
 int INTERRUPT_INFO ; 
 int INTERRUPT_RATE ; 
 int INTERRUPT_SUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_INT_FLG_CLR_TOP ; 
 int io_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tda1997x_irq_audio (struct tda1997x_state*,int*) ; 
 int /*<<< orphan*/  tda1997x_irq_ddc (struct tda1997x_state*,int*) ; 
 int /*<<< orphan*/  tda1997x_irq_hdcp (struct tda1997x_state*,int*) ; 
 int /*<<< orphan*/  tda1997x_irq_info (struct tda1997x_state*,int*) ; 
 int /*<<< orphan*/  tda1997x_irq_rate (struct tda1997x_state*,int*) ; 
 int /*<<< orphan*/  tda1997x_irq_sus (struct tda1997x_state*,int*) ; 

__attribute__((used)) static irqreturn_t tda1997x_isr_thread(int irq, void *d)
{
	struct tda1997x_state *state = d;
	struct v4l2_subdev *sd = &state->sd;
	u8 flags;

	mutex_lock(&state->lock);
	do {
		/* read interrupt flags */
		flags = io_read(sd, REG_INT_FLG_CLR_TOP);
		if (flags == 0)
			break;

		/* SUS interrupt source (Input activity events) */
		if (flags & INTERRUPT_SUS)
			tda1997x_irq_sus(state, &flags);
		/* DDC interrupt source (Display Data Channel) */
		else if (flags & INTERRUPT_DDC)
			tda1997x_irq_ddc(state, &flags);
		/* RATE interrupt source (Digital Input activity) */
		else if (flags & INTERRUPT_RATE)
			tda1997x_irq_rate(state, &flags);
		/* Infoframe change interrupt */
		else if (flags & INTERRUPT_INFO)
			tda1997x_irq_info(state, &flags);
		/* Audio interrupt source:
		 *   freq change, DST,OBA,HBR,ASP flags, mute, FIFO err
		 */
		else if (flags & INTERRUPT_AUDIO)
			tda1997x_irq_audio(state, &flags);
		/* HDCP interrupt source (content protection) */
		if (flags & INTERRUPT_HDCP)
			tda1997x_irq_hdcp(state, &flags);
	} while (flags != 0);
	mutex_unlock(&state->lock);

	return IRQ_HANDLED;
}