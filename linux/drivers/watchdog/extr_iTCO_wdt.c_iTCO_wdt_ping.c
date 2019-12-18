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
struct watchdog_device {int dummy; } ;
struct iTCO_wdt_private {int iTCO_version; int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCO1_STS (struct iTCO_wdt_private*) ; 
 int /*<<< orphan*/  TCO_RLD (struct iTCO_wdt_private*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct iTCO_wdt_private* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int iTCO_wdt_ping(struct watchdog_device *wd_dev)
{
	struct iTCO_wdt_private *p = watchdog_get_drvdata(wd_dev);

	spin_lock(&p->io_lock);

	/* Reload the timer by writing to the TCO Timer Counter register */
	if (p->iTCO_version >= 2) {
		outw(0x01, TCO_RLD(p));
	} else if (p->iTCO_version == 1) {
		/* Reset the timeout status bit so that the timer
		 * needs to count down twice again before rebooting */
		outw(0x0008, TCO1_STS(p));	/* write 1 to clear bit */

		outb(0x01, TCO_RLD(p));
	}

	spin_unlock(&p->io_lock);
	return 0;
}