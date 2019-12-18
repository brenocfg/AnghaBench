#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ PCL818_CTRL_REG ; 
 int /*<<< orphan*/  PCL818_CTRL_SOFT_TRIG ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pcl818_ai_clear_eoc (struct comedi_device*) ; 
 int /*<<< orphan*/  pcl818_ai_eoc ; 
 unsigned int pcl818_ai_get_sample (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcl818_ai_set_chan_range (struct comedi_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pcl818_ai_set_chan_scan (struct comedi_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pcl818_ai_soft_trig (struct comedi_device*) ; 

__attribute__((used)) static int pcl818_ai_insn_read(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	int ret = 0;
	int i;

	outb(PCL818_CTRL_SOFT_TRIG, dev->iobase + PCL818_CTRL_REG);

	pcl818_ai_set_chan_range(dev, chan, range);
	pcl818_ai_set_chan_scan(dev, chan, chan);

	for (i = 0; i < insn->n; i++) {
		pcl818_ai_clear_eoc(dev);
		pcl818_ai_soft_trig(dev);

		ret = comedi_timeout(dev, s, insn, pcl818_ai_eoc, 0);
		if (ret)
			break;

		data[i] = pcl818_ai_get_sample(dev, s, NULL);
	}
	pcl818_ai_clear_eoc(dev);

	return ret ? ret : insn->n;
}