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
struct comedi_device {struct comedi_subdevice* read_subdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  get_last_sample_611x (struct comedi_device*) ; 
 int /*<<< orphan*/  get_last_sample_6143 (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_ai_drain_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_handle_fifo_dregs (struct comedi_device*) ; 

__attribute__((used)) static void shutdown_ai_command(struct comedi_device *dev)
{
	struct comedi_subdevice *s = dev->read_subdev;

#ifdef PCIDMA
	ni_ai_drain_dma(dev);
#endif
	ni_handle_fifo_dregs(dev);
	get_last_sample_611x(dev);
	get_last_sample_6143(dev);

	s->async->events |= COMEDI_CB_EOA;
}