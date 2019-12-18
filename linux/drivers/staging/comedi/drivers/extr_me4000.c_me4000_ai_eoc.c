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
 int EBUSY ; 
 unsigned int ME4000_AI_STATUS_EF_DATA ; 
 scalar_t__ ME4000_AI_STATUS_REG ; 
 unsigned int inl (scalar_t__) ; 

__attribute__((used)) static int me4000_ai_eoc(struct comedi_device *dev,
			 struct comedi_subdevice *s,
			 struct comedi_insn *insn,
			 unsigned long context)
{
	unsigned int status;

	status = inl(dev->iobase + ME4000_AI_STATUS_REG);
	if (status & ME4000_AI_STATUS_EF_DATA)
		return 0;
	return -EBUSY;
}