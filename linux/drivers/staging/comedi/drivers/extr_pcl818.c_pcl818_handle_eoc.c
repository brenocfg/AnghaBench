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
struct TYPE_2__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pcl818_ai_eoc (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int pcl818_ai_get_sample (struct comedi_device*,struct comedi_subdevice*,unsigned int*) ; 
 int /*<<< orphan*/  pcl818_ai_write_sample (struct comedi_device*,struct comedi_subdevice*,unsigned int,unsigned int) ; 

__attribute__((used)) static void pcl818_handle_eoc(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	unsigned int chan;
	unsigned int val;

	if (pcl818_ai_eoc(dev, s, NULL, 0)) {
		dev_err(dev->class_dev, "A/D mode1/3 IRQ without DRDY!\n");
		s->async->events |= COMEDI_CB_ERROR;
		return;
	}

	val = pcl818_ai_get_sample(dev, s, &chan);
	pcl818_ai_write_sample(dev, s, chan, val);
}