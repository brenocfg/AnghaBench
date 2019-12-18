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
struct pci9111_private_data {int scan_delay; int chunk_num_samples; scalar_t__ chunk_counter; int /*<<< orphan*/  lcr_io_base; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  pacer; struct pci9111_private_data* private; } ;
struct comedi_cmd {int chanlist_len; scalar_t__ convert_src; scalar_t__ scan_begin_src; int scan_begin_arg; int convert_arg; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI9111_AI_CHANNEL_REG ; 
 unsigned int PCI9111_AI_RANGE (unsigned int) ; 
 scalar_t__ PCI9111_AI_RANGE_STAT_REG ; 
 unsigned int PCI9111_AI_TRIG_CTRL_ASCAN ; 
 unsigned int PCI9111_AI_TRIG_CTRL_ETIS ; 
 scalar_t__ PCI9111_AI_TRIG_CTRL_REG ; 
 unsigned int PCI9111_AI_TRIG_CTRL_TPST ; 
 scalar_t__ TRIG_TIMER ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  comedi_8254_update_divisors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_on_fifo_half_full ; 
 int /*<<< orphan*/  irq_on_timer_tick ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  pci9111_fifo_reset (struct comedi_device*) ; 
 int /*<<< orphan*/  pci9111_interrupt_source_set (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plx9050_interrupt_control (int /*<<< orphan*/ ,int,int,int,int,int) ; 

__attribute__((used)) static int pci9111_ai_do_cmd(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	struct pci9111_private_data *dev_private = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int last_chan = CR_CHAN(cmd->chanlist[cmd->chanlist_len - 1]);
	unsigned int range0 = CR_RANGE(cmd->chanlist[0]);
	unsigned int trig = 0;

	/*  Set channel scan limit */
	/*  PCI9111 allows only scanning from channel 0 to channel n */
	/*  TODO: handle the case of an external multiplexer */

	if (cmd->chanlist_len > 1)
		trig |= PCI9111_AI_TRIG_CTRL_ASCAN;

	outb(last_chan, dev->iobase + PCI9111_AI_CHANNEL_REG);

	/*  Set gain - all channels use the same range */
	outb(PCI9111_AI_RANGE(range0), dev->iobase + PCI9111_AI_RANGE_STAT_REG);

	/*  Set timer pacer */
	dev_private->scan_delay = 0;
	if (cmd->convert_src == TRIG_TIMER) {
		trig |= PCI9111_AI_TRIG_CTRL_TPST;
		comedi_8254_update_divisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
		pci9111_fifo_reset(dev);
		pci9111_interrupt_source_set(dev, irq_on_fifo_half_full,
					     irq_on_timer_tick);
		plx9050_interrupt_control(dev_private->lcr_io_base, true, true,
					  false, true, true);

		if (cmd->scan_begin_src == TRIG_TIMER) {
			dev_private->scan_delay = (cmd->scan_begin_arg /
				(cmd->convert_arg * cmd->chanlist_len)) - 1;
		}
	} else {	/* TRIG_EXT */
		trig |= PCI9111_AI_TRIG_CTRL_ETIS;
		pci9111_fifo_reset(dev);
		pci9111_interrupt_source_set(dev, irq_on_fifo_half_full,
					     irq_on_timer_tick);
		plx9050_interrupt_control(dev_private->lcr_io_base, true, true,
					  false, true, true);
	}
	outb(trig, dev->iobase + PCI9111_AI_TRIG_CTRL_REG);

	dev_private->chunk_counter = 0;
	dev_private->chunk_num_samples = cmd->chanlist_len *
					 (1 + dev_private->scan_delay);

	return 0;
}