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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int BUSY ; 
 scalar_t__ DAS800_STATUS ; 
 int EBUSY ; 
 unsigned int inb (scalar_t__) ; 

__attribute__((used)) static int das800_ai_eoc(struct comedi_device *dev,
			 struct comedi_subdevice *s,
			 struct comedi_insn *insn,
			 unsigned long context)
{
	unsigned int status;

	status = inb(dev->iobase + DAS800_STATUS);
	if ((status & BUSY) == 0)
		return 0;
	return -EBUSY;
}