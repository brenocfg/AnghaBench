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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ ADQ12B_STINR ; 
 unsigned int ADQ12B_STINR_IN_MASK ; 
 unsigned int inb (scalar_t__) ; 

__attribute__((used)) static int adq12b_di_insn_bits(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{
	/* only bits 0-4 have information about digital inputs */
	data[1] = (inb(dev->iobase + ADQ12B_STINR) & ADQ12B_STINR_IN_MASK);

	return insn->n;
}