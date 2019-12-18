#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; } ;
struct comedi_cmd {scalar_t__ stop_src; } ;
struct TYPE_2__ {int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 int /*<<< orphan*/  COMEDI_CB_OVERFLOW ; 
 unsigned short NISTC_AI_STATUS1_ERR ; 
 unsigned short NISTC_AI_STATUS1_FIFO_HF ; 
 unsigned short NISTC_AI_STATUS1_OVER ; 
 int /*<<< orphan*/  NISTC_AI_STATUS1_REG ; 
 unsigned short NISTC_AI_STATUS1_SC_TC ; 
 unsigned short NISTC_AI_STATUS1_START1 ; 
 unsigned short NISTC_AI_STATUS1_STOP ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ comedi_is_subdevice_running (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ni_handle_eos (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  ni_handle_fifo_half_full (struct comedi_device*) ; 
 unsigned short ni_stc_readw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_ai_command (struct comedi_device*) ; 

__attribute__((used)) static void handle_a_interrupt(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       unsigned short status)
{
	struct comedi_cmd *cmd = &s->async->cmd;

	/* test for all uncommon interrupt events at the same time */
	if (status & (NISTC_AI_STATUS1_ERR |
		      NISTC_AI_STATUS1_SC_TC | NISTC_AI_STATUS1_START1)) {
		if (status == 0xffff) {
			dev_err(dev->class_dev, "Card removed?\n");
			/*
			 * We probably aren't even running a command now,
			 * so it's a good idea to be careful.
			 */
			if (comedi_is_subdevice_running(s))
				s->async->events |= COMEDI_CB_ERROR;
			return;
		}
		if (status & NISTC_AI_STATUS1_ERR) {
			dev_err(dev->class_dev, "ai error a_status=%04x\n",
				status);

			shutdown_ai_command(dev);

			s->async->events |= COMEDI_CB_ERROR;
			if (status & NISTC_AI_STATUS1_OVER)
				s->async->events |= COMEDI_CB_OVERFLOW;
			return;
		}
		if (status & NISTC_AI_STATUS1_SC_TC) {
			if (cmd->stop_src == TRIG_COUNT)
				shutdown_ai_command(dev);
		}
	}
#ifndef PCIDMA
	if (status & NISTC_AI_STATUS1_FIFO_HF) {
		int i;
		static const int timeout = 10;
		/*
		 * PCMCIA cards (at least 6036) seem to stop producing
		 * interrupts if we fail to get the fifo less than half
		 * full, so loop to be sure.
		 */
		for (i = 0; i < timeout; ++i) {
			ni_handle_fifo_half_full(dev);
			if ((ni_stc_readw(dev, NISTC_AI_STATUS1_REG) &
			     NISTC_AI_STATUS1_FIFO_HF) == 0)
				break;
		}
	}
#endif /*  !PCIDMA */

	if (status & NISTC_AI_STATUS1_STOP)
		ni_handle_eos(dev, s);
}