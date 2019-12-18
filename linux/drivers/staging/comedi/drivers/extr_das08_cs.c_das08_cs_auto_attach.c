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
struct das08_private_struct {int dummy; } ;
struct comedi_device {int /*<<< orphan*/ * board_ptr; } ;
struct TYPE_2__ {unsigned long start; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_AUTO_SET_IO ; 
 int ENOMEM ; 
 struct das08_private_struct* comedi_alloc_devpriv (struct comedi_device*,int) ; 
 int comedi_pcmcia_enable (struct comedi_device*,int /*<<< orphan*/ *) ; 
 struct pcmcia_device* comedi_to_pcmcia_dev (struct comedi_device*) ; 
 int das08_common_attach (struct comedi_device*,unsigned long) ; 
 int /*<<< orphan*/ * das08_cs_boards ; 

__attribute__((used)) static int das08_cs_auto_attach(struct comedi_device *dev,
				unsigned long context)
{
	struct pcmcia_device *link = comedi_to_pcmcia_dev(dev);
	struct das08_private_struct *devpriv;
	unsigned long iobase;
	int ret;

	/* The das08 driver needs the board_ptr */
	dev->board_ptr = &das08_cs_boards[0];

	link->config_flags |= CONF_AUTO_SET_IO;
	ret = comedi_pcmcia_enable(dev, NULL);
	if (ret)
		return ret;
	iobase = link->resource[0]->start;

	devpriv = comedi_alloc_devpriv(dev, sizeof(*devpriv));
	if (!devpriv)
		return -ENOMEM;

	return das08_common_attach(dev, iobase);
}