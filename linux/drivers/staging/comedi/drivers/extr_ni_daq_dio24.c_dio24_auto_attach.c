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
struct pcmcia_device {TYPE_1__** resource; int /*<<< orphan*/  config_flags; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct comedi_subdevice* subdevices; int /*<<< orphan*/  iobase; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_AUTO_SET_IO ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int comedi_pcmcia_enable (struct comedi_device*,int /*<<< orphan*/ *) ; 
 struct pcmcia_device* comedi_to_pcmcia_dev (struct comedi_device*) ; 
 int subdev_8255_init (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dio24_auto_attach(struct comedi_device *dev,
			     unsigned long context)
{
	struct pcmcia_device *link = comedi_to_pcmcia_dev(dev);
	struct comedi_subdevice *s;
	int ret;

	link->config_flags |= CONF_AUTO_SET_IO;
	ret = comedi_pcmcia_enable(dev, NULL);
	if (ret)
		return ret;
	dev->iobase = link->resource[0]->start;

	ret = comedi_alloc_subdevices(dev, 1);
	if (ret)
		return ret;

	/* 8255 dio */
	s = &dev->subdevices[0];
	return subdev_8255_init(dev, s, NULL, 0x00);
}