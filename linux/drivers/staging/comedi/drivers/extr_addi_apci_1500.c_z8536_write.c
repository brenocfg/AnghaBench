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
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI1500_Z8536_CTRL_REG ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void z8536_write(struct comedi_device *dev,
			unsigned int val, unsigned int reg)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	outb(reg, dev->iobase + APCI1500_Z8536_CTRL_REG);
	outb(val, dev->iobase + APCI1500_Z8536_CTRL_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);
}