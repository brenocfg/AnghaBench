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
struct ni_private {scalar_t__ is_m_series; scalar_t__ is_6xxx; } ;
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int NI671X_AO_IMMEDIATE_REG ; 
 int NI671X_DAC_DIRECT_DATA_REG (unsigned int) ; 
 int NI_E_DAC_DIRECT_DATA_REG (unsigned int) ; 
 int NI_M_DAC_DIRECT_DATA_REG (unsigned int) ; 
 unsigned int comedi_offset_munge (struct comedi_subdevice*,unsigned int) ; 
 scalar_t__ comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  ni_ao_config_chanlist (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_ao_win_outw (struct comedi_device*,unsigned int,int) ; 
 int /*<<< orphan*/  ni_writew (struct comedi_device*,unsigned int,int) ; 

__attribute__((used)) static int ni_ao_insn_write(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn,
			    unsigned int *data)
{
	struct ni_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	int reg;
	int i;

	if (devpriv->is_6xxx) {
		ni_ao_win_outw(dev, 1 << chan, NI671X_AO_IMMEDIATE_REG);

		reg = NI671X_DAC_DIRECT_DATA_REG(chan);
	} else if (devpriv->is_m_series) {
		reg = NI_M_DAC_DIRECT_DATA_REG(chan);
	} else {
		reg = NI_E_DAC_DIRECT_DATA_REG(chan);
	}

	ni_ao_config_chanlist(dev, s, &insn->chanspec, 1, 0);

	for (i = 0; i < insn->n; i++) {
		unsigned int val = data[i];

		s->readback[chan] = val;

		if (devpriv->is_6xxx) {
			/*
			 * 6xxx boards have bipolar outputs, munge the
			 * unsigned comedi values to 2's complement
			 */
			val = comedi_offset_munge(s, val);

			ni_ao_win_outw(dev, val, reg);
		} else if (devpriv->is_m_series) {
			/*
			 * M-series boards use offset binary values for
			 * bipolar and uinpolar outputs
			 */
			ni_writew(dev, val, reg);
		} else {
			/*
			 * Non-M series boards need two's complement values
			 * for bipolar ranges.
			 */
			if (comedi_range_is_bipolar(s, range))
				val = comedi_offset_munge(s, val);

			ni_writew(dev, val, reg);
		}
	}

	return insn->n;
}