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
struct pcmmio_private {unsigned int enabled_mask; int active; } ;
struct comedi_subdevice {int n_chan; TYPE_1__* async; } ;
struct comedi_device {struct pcmmio_private* private; } ;
struct comedi_cmd {unsigned int* chanlist; int chanlist_len; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 unsigned int CR_AREF (unsigned int) ; 
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 
 int /*<<< orphan*/  PCMMIO_PAGE_ENAB ; 
 int /*<<< orphan*/  PCMMIO_PAGE_POL ; 
 int /*<<< orphan*/  pcmmio_dio_write (struct comedi_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcmmio_start_intr(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	struct pcmmio_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int bits = 0;
	unsigned int pol_bits = 0;
	int i;

	devpriv->enabled_mask = 0;
	devpriv->active = 1;
	if (cmd->chanlist) {
		for (i = 0; i < cmd->chanlist_len; i++) {
			unsigned int chanspec = cmd->chanlist[i];
			unsigned int chan = CR_CHAN(chanspec);
			unsigned int range = CR_RANGE(chanspec);
			unsigned int aref = CR_AREF(chanspec);

			bits |= (1 << chan);
			pol_bits |= (((aref || range) ? 1 : 0) << chan);
		}
	}
	bits &= ((1 << s->n_chan) - 1);
	devpriv->enabled_mask = bits;

	/* set polarity and enable interrupts */
	pcmmio_dio_write(dev, pol_bits, PCMMIO_PAGE_POL, 0);
	pcmmio_dio_write(dev, bits, PCMMIO_PAGE_ENAB, 0);
}