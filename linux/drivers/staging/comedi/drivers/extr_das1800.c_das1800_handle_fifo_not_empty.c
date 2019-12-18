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
struct comedi_device {scalar_t__ iobase; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct TYPE_2__ {scalar_t__ scans_done; struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ DAS1800_FIFO ; 
 scalar_t__ DAS1800_STATUS ; 
 int FNE ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 int inb (scalar_t__) ; 
 unsigned short inw (scalar_t__) ; 

__attribute__((used)) static void das1800_handle_fifo_not_empty(struct comedi_device *dev,
					  struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned short dpnt;

	while (inb(dev->iobase + DAS1800_STATUS) & FNE) {
		dpnt = inw(dev->iobase + DAS1800_FIFO);
		comedi_buf_write_samples(s, &dpnt, 1);

		if (cmd->stop_src == TRIG_COUNT &&
		    s->async->scans_done >= cmd->stop_arg)
			break;
	}
}