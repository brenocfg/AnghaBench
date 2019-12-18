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
struct rtd_private {scalar_t__ las1; } ;
struct comedi_subdevice {unsigned short maxdata; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ mmio; struct rtd_private* private; } ;

/* Variables and functions */
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ LAS0_ADC ; 
 scalar_t__ LAS0_ADC_CONVERSION ; 
 scalar_t__ LAS0_ADC_FIFO_CLEAR ; 
 scalar_t__ LAS1_ADC_FIFO ; 
 unsigned short comedi_offset_munge (struct comedi_subdevice*,unsigned short) ; 
 scalar_t__ comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned short readw (scalar_t__) ; 
 int /*<<< orphan*/  rtd_ai_eoc ; 
 int /*<<< orphan*/  rtd_load_channelgain_list (struct comedi_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rtd_ai_rinsn(struct comedi_device *dev,
			struct comedi_subdevice *s, struct comedi_insn *insn,
			unsigned int *data)
{
	struct rtd_private *devpriv = dev->private;
	unsigned int range = CR_RANGE(insn->chanspec);
	int ret;
	int n;

	/* clear any old fifo data */
	writel(0, dev->mmio + LAS0_ADC_FIFO_CLEAR);

	/* write channel to multiplexer and clear channel gain table */
	rtd_load_channelgain_list(dev, 1, &insn->chanspec);

	/* ADC conversion trigger source: SOFTWARE */
	writel(0, dev->mmio + LAS0_ADC_CONVERSION);

	/* convert n samples */
	for (n = 0; n < insn->n; n++) {
		unsigned short d;
		/* trigger conversion */
		writew(0, dev->mmio + LAS0_ADC);

		ret = comedi_timeout(dev, s, insn, rtd_ai_eoc, 0);
		if (ret)
			return ret;

		/* read data */
		d = readw(devpriv->las1 + LAS1_ADC_FIFO);
		d >>= 3;	/* low 3 bits are marker lines */

		/* convert bipolar data to comedi unsigned data */
		if (comedi_range_is_bipolar(s, range))
			d = comedi_offset_munge(s, d);

		data[n] = d & s->maxdata;
	}

	/* return the number of samples read/written */
	return n;
}