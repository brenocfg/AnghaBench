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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI3120_CTRL_REG ; 
 scalar_t__ APCI3120_MODE_REG ; 
 scalar_t__ APCI3120_STATUS_REG ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void apci3120_reset(struct comedi_device *dev)
{
	/* disable all interrupt sources */
	outb(0, dev->iobase + APCI3120_MODE_REG);

	/* disable all counters, ext trigger, and reset scan */
	outw(0, dev->iobase + APCI3120_CTRL_REG);

	/* clear interrupt status */
	inw(dev->iobase + APCI3120_STATUS_REG);
}