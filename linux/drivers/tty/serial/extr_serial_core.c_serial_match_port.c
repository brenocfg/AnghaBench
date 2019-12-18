#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_match {TYPE_2__* port; TYPE_1__* driver; } ;
struct tty_driver {int /*<<< orphan*/  minor_start; int /*<<< orphan*/  major; } ;
struct device {scalar_t__ devt; } ;
typedef  scalar_t__ dev_t ;
struct TYPE_4__ {scalar_t__ line; } ;
struct TYPE_3__ {struct tty_driver* tty_driver; } ;

/* Variables and functions */
 scalar_t__ MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int serial_match_port(struct device *dev, void *data)
{
	struct uart_match *match = data;
	struct tty_driver *tty_drv = match->driver->tty_driver;
	dev_t devt = MKDEV(tty_drv->major, tty_drv->minor_start) +
		match->port->line;

	return dev->devt == devt; /* Actually, only one tty per port */
}