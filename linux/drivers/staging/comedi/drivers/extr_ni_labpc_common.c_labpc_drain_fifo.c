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
struct labpc_private {int stat1; int (* read_byte ) (struct comedi_device*,int /*<<< orphan*/ ) ;scalar_t__ count; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; TYPE_1__* read_subdev; struct labpc_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; } ;
struct comedi_async {int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;
struct TYPE_2__ {struct comedi_async* async; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 int STAT1_DAVAIL ; 
 int /*<<< orphan*/  STAT1_REG ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_write_samples (TYPE_1__*,unsigned short*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned short labpc_read_adc_fifo (struct comedi_device*) ; 
 int stub1 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int stub2 (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int labpc_drain_fifo(struct comedi_device *dev)
{
	struct labpc_private *devpriv = dev->private;
	struct comedi_async *async = dev->read_subdev->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned short data;
	const int timeout = 10000;
	unsigned int i;

	devpriv->stat1 = devpriv->read_byte(dev, STAT1_REG);

	for (i = 0; (devpriv->stat1 & STAT1_DAVAIL) && i < timeout;
	     i++) {
		/*  quit if we have all the data we want */
		if (cmd->stop_src == TRIG_COUNT) {
			if (devpriv->count == 0)
				break;
			devpriv->count--;
		}
		data = labpc_read_adc_fifo(dev);
		comedi_buf_write_samples(dev->read_subdev, &data, 1);
		devpriv->stat1 = devpriv->read_byte(dev, STAT1_REG);
	}
	if (i == timeout) {
		dev_err(dev->class_dev, "ai timeout, fifo never empties\n");
		async->events |= COMEDI_CB_ERROR;
		return -1;
	}

	return 0;
}