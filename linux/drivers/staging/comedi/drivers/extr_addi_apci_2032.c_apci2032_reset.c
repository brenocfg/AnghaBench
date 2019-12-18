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
 scalar_t__ APCI2032_DO_REG ; 
 scalar_t__ APCI2032_INT_CTRL_REG ; 
 scalar_t__ APCI2032_WDOG_REG ; 
 int /*<<< orphan*/  addi_watchdog_reset (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static int apci2032_reset(struct comedi_device *dev)
{
	outl(0x0, dev->iobase + APCI2032_DO_REG);
	outl(0x0, dev->iobase + APCI2032_INT_CTRL_REG);

	addi_watchdog_reset(dev->iobase + APCI2032_WDOG_REG);

	return 0;
}