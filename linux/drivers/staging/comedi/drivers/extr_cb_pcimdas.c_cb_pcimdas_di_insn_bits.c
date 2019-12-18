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
struct comedi_insn {int n; } ;
struct comedi_device {struct cb_pcimdas_private* private; } ;
struct cb_pcimdas_private {scalar_t__ BADR3; } ;

/* Variables and functions */
 scalar_t__ PCIMDAS_DI_DO_REG ; 
 unsigned int inb (scalar_t__) ; 

__attribute__((used)) static int cb_pcimdas_di_insn_bits(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	struct cb_pcimdas_private *devpriv = dev->private;
	unsigned int val;

	val = inb(devpriv->BADR3 + PCIMDAS_DI_DO_REG);

	data[1] = val & 0x0f;

	return insn->n;
}