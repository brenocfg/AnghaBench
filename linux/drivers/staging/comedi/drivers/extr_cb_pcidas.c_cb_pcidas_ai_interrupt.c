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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct comedi_subdevice* read_subdev; struct cb_pcidas_private* private; struct cb_pcidas_board* board_ptr; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct comedi_async {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;
struct cb_pcidas_private {unsigned short* ai_buffer; scalar_t__ pcibar2; scalar_t__ pcibar1; } ;
struct cb_pcidas_board {int fifo_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 scalar_t__ PCIDAS_AI_DATA_REG ; 
 unsigned int PCIDAS_CTRL_ADHFI ; 
 unsigned short PCIDAS_CTRL_ADNE ; 
 unsigned int PCIDAS_CTRL_ADNEI ; 
 unsigned int PCIDAS_CTRL_EOAI ; 
 unsigned int PCIDAS_CTRL_EOBI ; 
 unsigned int PCIDAS_CTRL_INT_CLR ; 
 unsigned int PCIDAS_CTRL_LADFUL ; 
 scalar_t__ PCIDAS_CTRL_REG ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int comedi_nsamples_left (struct comedi_subdevice*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  insw (scalar_t__,unsigned short*,unsigned int) ; 
 unsigned short inw (scalar_t__) ; 

__attribute__((used)) static unsigned int cb_pcidas_ai_interrupt(struct comedi_device *dev,
					   unsigned int status)
{
	const struct cb_pcidas_board *board = dev->board_ptr;
	struct cb_pcidas_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int irq_clr = 0;

	if (status & PCIDAS_CTRL_ADHFI) {
		unsigned int num_samples;

		irq_clr |= PCIDAS_CTRL_INT_CLR;

		/* FIFO is half-full - read data */
		num_samples = comedi_nsamples_left(s, board->fifo_size / 2);
		insw(devpriv->pcibar2 + PCIDAS_AI_DATA_REG,
		     devpriv->ai_buffer, num_samples);
		comedi_buf_write_samples(s, devpriv->ai_buffer, num_samples);

		if (cmd->stop_src == TRIG_COUNT &&
		    async->scans_done >= cmd->stop_arg)
			async->events |= COMEDI_CB_EOA;
	} else if (status & (PCIDAS_CTRL_ADNEI | PCIDAS_CTRL_EOBI)) {
		unsigned int i;

		irq_clr |= PCIDAS_CTRL_INT_CLR;

		/* FIFO is not empty - read data until empty or timeoout */
		for (i = 0; i < 10000; i++) {
			unsigned short val;

			/*  break if fifo is empty */
			if ((inw(devpriv->pcibar1 + PCIDAS_CTRL_REG) &
			    PCIDAS_CTRL_ADNE) == 0)
				break;
			val = inw(devpriv->pcibar2 + PCIDAS_AI_DATA_REG);
			comedi_buf_write_samples(s, &val, 1);

			if (cmd->stop_src == TRIG_COUNT &&
			    async->scans_done >= cmd->stop_arg) {
				async->events |= COMEDI_CB_EOA;
				break;
			}
		}
	} else if (status & PCIDAS_CTRL_EOAI) {
		irq_clr |= PCIDAS_CTRL_EOAI;

		dev_err(dev->class_dev,
			"bug! encountered end of acquisition interrupt?\n");
	}

	/* check for fifo overflow */
	if (status & PCIDAS_CTRL_LADFUL) {
		irq_clr |= PCIDAS_CTRL_LADFUL;

		dev_err(dev->class_dev, "fifo overflow\n");
		async->events |= COMEDI_CB_ERROR;
	}

	comedi_handle_events(dev, s);

	return irq_clr;
}