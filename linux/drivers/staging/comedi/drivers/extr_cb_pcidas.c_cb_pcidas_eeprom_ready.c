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
struct comedi_insn {int dummy; } ;
struct comedi_device {struct cb_pcidas_private* private; } ;
struct cb_pcidas_private {scalar_t__ amcc; } ;

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_MCSR_NVCMD ; 
 int EBUSY ; 
 unsigned int MCSR_NV_BUSY ; 
 unsigned int inb (scalar_t__) ; 

__attribute__((used)) static int cb_pcidas_eeprom_ready(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn,
				  unsigned long context)
{
	struct cb_pcidas_private *devpriv = dev->private;
	unsigned int status;

	status = inb(devpriv->amcc + AMCC_OP_REG_MCSR_NVCMD);
	if ((status & MCSR_NV_BUSY) == 0)
		return 0;
	return -EBUSY;
}