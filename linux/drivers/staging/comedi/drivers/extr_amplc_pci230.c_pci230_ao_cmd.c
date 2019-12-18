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
struct pci230_private {int hwver; unsigned short daccon; scalar_t__ daqio; scalar_t__ ao_bipolar; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; struct pci230_private* private; } ;
struct comedi_cmd {scalar_t__ scan_begin_src; unsigned int chanlist_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  scan_begin_arg; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  GAT_GND ; 
 int /*<<< orphan*/  I8254_MODE3 ; 
 int /*<<< orphan*/  OWNER_AOCMD ; 
 scalar_t__ PCI230P2_DACEN ; 
 unsigned short PCI230P2_DAC_FIFO_EN ; 
 unsigned short PCI230P2_DAC_FIFO_RESET ; 
 unsigned short PCI230P2_DAC_FIFO_UNDERRUN_CLEAR ; 
 unsigned short PCI230P2_DAC_INT_FIFO_NHALF ; 
 unsigned short PCI230P2_DAC_TRIG_NONE ; 
 scalar_t__ PCI230_DACCON ; 
 unsigned short PCI230_DAC_OR_BIP ; 
 unsigned short PCI230_DAC_OR_UNI ; 
 scalar_t__ PCI230_ZGAT_SCE ; 
 int /*<<< orphan*/  RES_Z2CT1 ; 
 scalar_t__ TRIG_TIMER ; 
 scalar_t__ comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  pci230_ao_inttrig_start ; 
 int /*<<< orphan*/  pci230_claim_shared (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci230_ct_setup_ns_mode (struct comedi_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci230_gat_config (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci230_ao_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct pci230_private *devpriv = dev->private;
	unsigned short daccon;
	unsigned int range;

	/* Get the command. */
	struct comedi_cmd *cmd = &s->async->cmd;

	if (cmd->scan_begin_src == TRIG_TIMER) {
		/* Claim Z2-CT1. */
		if (!pci230_claim_shared(dev, RES_Z2CT1, OWNER_AOCMD))
			return -EBUSY;
	}

	/*
	 * Set range - see analogue output range table; 0 => unipolar 10V,
	 * 1 => bipolar +/-10V range scale
	 */
	range = CR_RANGE(cmd->chanlist[0]);
	devpriv->ao_bipolar = comedi_range_is_bipolar(s, range);
	daccon = devpriv->ao_bipolar ? PCI230_DAC_OR_BIP : PCI230_DAC_OR_UNI;
	/* Use DAC FIFO for hardware version 2 onwards. */
	if (devpriv->hwver >= 2) {
		unsigned short dacen;
		unsigned int i;

		dacen = 0;
		for (i = 0; i < cmd->chanlist_len; i++)
			dacen |= 1 << CR_CHAN(cmd->chanlist[i]);

		/* Set channel scan list. */
		outw(dacen, devpriv->daqio + PCI230P2_DACEN);
		/*
		 * Enable DAC FIFO.
		 * Set DAC scan source to 'none'.
		 * Set DAC FIFO interrupt trigger level to 'not half full'.
		 * Reset DAC FIFO and clear underrun.
		 *
		 * N.B. DAC FIFO interrupts are currently disabled.
		 */
		daccon |= PCI230P2_DAC_FIFO_EN | PCI230P2_DAC_FIFO_RESET |
			  PCI230P2_DAC_FIFO_UNDERRUN_CLEAR |
			  PCI230P2_DAC_TRIG_NONE | PCI230P2_DAC_INT_FIFO_NHALF;
	}

	/* Set DACCON. */
	outw(daccon, devpriv->daqio + PCI230_DACCON);
	/* Preserve most of DACCON apart from write-only, transient bits. */
	devpriv->daccon = daccon & ~(PCI230P2_DAC_FIFO_RESET |
				     PCI230P2_DAC_FIFO_UNDERRUN_CLEAR);

	if (cmd->scan_begin_src == TRIG_TIMER) {
		/*
		 * Set the counter timer 1 to the specified scan frequency.
		 * cmd->scan_begin_arg is sampling period in ns.
		 * Gate it off for now.
		 */
		outb(pci230_gat_config(1, GAT_GND),
		     dev->iobase + PCI230_ZGAT_SCE);
		pci230_ct_setup_ns_mode(dev, 1, I8254_MODE3,
					cmd->scan_begin_arg,
					cmd->flags);
	}

	/* N.B. cmd->start_src == TRIG_INT */
	s->async->inttrig = pci230_ao_inttrig_start;

	return 0;
}