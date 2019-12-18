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
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int DB2K_DAC_STATUS_DAC_BUSY (unsigned int) ; 
 scalar_t__ DB2K_REG_DAC_STATUS ; 
 int EBUSY ; 
 unsigned int readw (scalar_t__) ; 

__attribute__((used)) static int db2k_ao_eoc(struct comedi_device *dev, struct comedi_subdevice *s,
		       struct comedi_insn *insn, unsigned long context)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int status;

	status = readw(dev->mmio + DB2K_REG_DAC_STATUS);
	if ((status & DB2K_DAC_STATUS_DAC_BUSY(chan)) == 0)
		return 0;
	return -EBUSY;
}