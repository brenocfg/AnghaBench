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
 int /*<<< orphan*/  DMM32AT_AI_READBACK_REG ; 
 scalar_t__ DMM32AT_AI_START_CONV_REG ; 
 int /*<<< orphan*/  DMM32AT_AI_STATUS_REG ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int dmm32at_ai_get_sample (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dmm32at_ai_set_chanspec (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmm32at_ai_status ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int dmm32at_ai_insn_read(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	int ret;
	int i;

	dmm32at_ai_set_chanspec(dev, s, insn->chanspec, 1);

	/* wait for circuit to settle */
	ret = comedi_timeout(dev, s, insn, dmm32at_ai_status,
			     DMM32AT_AI_READBACK_REG);
	if (ret)
		return ret;

	for (i = 0; i < insn->n; i++) {
		outb(0xff, dev->iobase + DMM32AT_AI_START_CONV_REG);

		ret = comedi_timeout(dev, s, insn, dmm32at_ai_status,
				     DMM32AT_AI_STATUS_REG);
		if (ret)
			return ret;

		data[i] = dmm32at_ai_get_sample(dev, s);
	}

	return insn->n;
}