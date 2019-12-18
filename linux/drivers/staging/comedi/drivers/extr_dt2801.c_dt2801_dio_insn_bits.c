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
struct comedi_subdevice {int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {struct comedi_subdevice* subdevices; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_C_READ_DIG ; 
 int /*<<< orphan*/  DT_C_WRITE_DIG ; 
 scalar_t__ comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 int /*<<< orphan*/  dt2801_readdata (struct comedi_device*,unsigned int*) ; 
 int /*<<< orphan*/  dt2801_writecmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt2801_writedata (struct comedi_device*,int) ; 

__attribute__((used)) static int dt2801_dio_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	int which = (s == &dev->subdevices[3]) ? 1 : 0;
	unsigned int val = 0;

	if (comedi_dio_update_state(s, data)) {
		dt2801_writecmd(dev, DT_C_WRITE_DIG);
		dt2801_writedata(dev, which);
		dt2801_writedata(dev, s->state);
	}

	dt2801_writecmd(dev, DT_C_READ_DIG);
	dt2801_writedata(dev, which);
	dt2801_readdata(dev, &val);

	data[1] = val;

	return insn->n;
}