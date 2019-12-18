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
struct comedi_insn {unsigned int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct cb_pcidda_private* private; } ;
struct cb_pcidda_private {unsigned int* ao_range; scalar_t__ daqio; } ;

/* Variables and functions */
 unsigned int CB_DDA_DA_CTRL_DAC (unsigned int) ; 
 unsigned int CB_DDA_DA_CTRL_EN ; 
 unsigned int CB_DDA_DA_CTRL_RANGE10V ; 
 unsigned int CB_DDA_DA_CTRL_RANGE2V5 ; 
 unsigned int CB_DDA_DA_CTRL_RANGE5V ; 
 scalar_t__ CB_DDA_DA_CTRL_REG ; 
 unsigned int CB_DDA_DA_CTRL_UNIP ; 
 scalar_t__ CB_DDA_DA_DATA_REG (unsigned int) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb_pcidda_calibrate (struct comedi_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 

__attribute__((used)) static int cb_pcidda_ao_insn_write(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	struct cb_pcidda_private *devpriv = dev->private;
	unsigned int channel = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	unsigned int ctrl;
	unsigned int i;

	if (range != devpriv->ao_range[channel])
		cb_pcidda_calibrate(dev, channel, range);

	ctrl = CB_DDA_DA_CTRL_EN | CB_DDA_DA_CTRL_DAC(channel);

	switch (range) {
	case 0:
	case 3:
		ctrl |= CB_DDA_DA_CTRL_RANGE10V;
		break;
	case 1:
	case 4:
		ctrl |= CB_DDA_DA_CTRL_RANGE5V;
		break;
	case 2:
	case 5:
		ctrl |= CB_DDA_DA_CTRL_RANGE2V5;
		break;
	}

	if (range > 2)
		ctrl |= CB_DDA_DA_CTRL_UNIP;

	outw(ctrl, devpriv->daqio + CB_DDA_DA_CTRL_REG);

	for (i = 0; i < insn->n; i++)
		outw(data[i], devpriv->daqio + CB_DDA_DA_DATA_REG(channel));

	return insn->n;
}