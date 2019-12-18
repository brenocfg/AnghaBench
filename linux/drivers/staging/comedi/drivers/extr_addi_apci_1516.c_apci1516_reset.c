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
struct comedi_device {scalar_t__ iobase; struct apci1516_private* private; struct apci1516_boardinfo* board_ptr; } ;
struct apci1516_private {int /*<<< orphan*/  wdog_iobase; } ;
struct apci1516_boardinfo {int /*<<< orphan*/  has_wdog; } ;

/* Variables and functions */
 scalar_t__ APCI1516_DO_REG ; 
 int /*<<< orphan*/  addi_watchdog_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int apci1516_reset(struct comedi_device *dev)
{
	const struct apci1516_boardinfo *board = dev->board_ptr;
	struct apci1516_private *devpriv = dev->private;

	if (!board->has_wdog)
		return 0;

	outw(0x0, dev->iobase + APCI1516_DO_REG);

	addi_watchdog_reset(devpriv->wdog_iobase);

	return 0;
}