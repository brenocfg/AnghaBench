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
struct pcmuio_private {struct pcmuio_asic* asics; } ;
struct pcmuio_asic {unsigned int enabled_mask; int active; } ;
struct comedi_subdevice {int n_chan; TYPE_1__* async; } ;
struct comedi_device {struct pcmuio_private* private; } ;
struct comedi_cmd {unsigned int* chanlist; int chanlist_len; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 unsigned int CR_AREF (unsigned int) ; 
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 
 int /*<<< orphan*/  PCMUIO_PAGE_ENAB ; 
 int /*<<< orphan*/  PCMUIO_PAGE_POL ; 
 int pcmuio_subdevice_to_asic (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pcmuio_write (struct comedi_device*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcmuio_start_intr(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	struct pcmuio_private *devpriv = dev->private;
	int asic = pcmuio_subdevice_to_asic(s);
	struct pcmuio_asic *chip = &devpriv->asics[asic];
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int bits = 0;
	unsigned int pol_bits = 0;
	int i;

	chip->enabled_mask = 0;
	chip->active = 1;
	if (cmd->chanlist) {
		for (i = 0; i < cmd->chanlist_len; i++) {
			unsigned int chanspec = cmd->chanlist[i];
			unsigned int chan = CR_CHAN(chanspec);
			unsigned int range = CR_RANGE(chanspec);
			unsigned int aref = CR_AREF(chanspec);

			bits |= (1 << chan);
			pol_bits |= ((aref || range) ? 1 : 0) << chan;
		}
	}
	bits &= ((1 << s->n_chan) - 1);
	chip->enabled_mask = bits;

	/* set pol and enab intrs for this subdev.. */
	pcmuio_write(dev, pol_bits, asic, PCMUIO_PAGE_POL, 0);
	pcmuio_write(dev, bits, asic, PCMUIO_PAGE_ENAB, 0);
}