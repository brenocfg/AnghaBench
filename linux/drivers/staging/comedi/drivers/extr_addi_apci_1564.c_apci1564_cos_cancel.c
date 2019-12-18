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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI1564_DI_INT_MODE1_REG ; 
 scalar_t__ APCI1564_DI_INT_MODE2_REG ; 
 scalar_t__ APCI1564_DI_INT_STATUS_REG ; 
 scalar_t__ APCI1564_DI_IRQ_REG ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static int apci1564_cos_cancel(struct comedi_device *dev,
			       struct comedi_subdevice *s)
{
	outl(0x0, dev->iobase + APCI1564_DI_IRQ_REG);
	inl(dev->iobase + APCI1564_DI_INT_STATUS_REG);
	outl(0x0, dev->iobase + APCI1564_DI_INT_MODE1_REG);
	outl(0x0, dev->iobase + APCI1564_DI_INT_MODE2_REG);

	return 0;
}