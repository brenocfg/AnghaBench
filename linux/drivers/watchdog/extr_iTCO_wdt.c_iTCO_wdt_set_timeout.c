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
struct watchdog_device {unsigned int timeout; } ;
struct iTCO_wdt_private {int iTCO_version; int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TCOv1_TMR (struct iTCO_wdt_private*) ; 
 int /*<<< orphan*/  TCOv2_TMR (struct iTCO_wdt_private*) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 unsigned int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int seconds_to_ticks (struct iTCO_wdt_private*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct iTCO_wdt_private* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int iTCO_wdt_set_timeout(struct watchdog_device *wd_dev, unsigned int t)
{
	struct iTCO_wdt_private *p = watchdog_get_drvdata(wd_dev);
	unsigned int val16;
	unsigned char val8;
	unsigned int tmrval;

	tmrval = seconds_to_ticks(p, t);

	/* For TCO v1 the timer counts down twice before rebooting */
	if (p->iTCO_version == 1)
		tmrval /= 2;

	/* from the specs: */
	/* "Values of 0h-3h are ignored and should not be attempted" */
	if (tmrval < 0x04)
		return -EINVAL;
	if ((p->iTCO_version >= 2 && tmrval > 0x3ff) ||
	    (p->iTCO_version == 1 && tmrval > 0x03f))
		return -EINVAL;

	/* Write new heartbeat to watchdog */
	if (p->iTCO_version >= 2) {
		spin_lock(&p->io_lock);
		val16 = inw(TCOv2_TMR(p));
		val16 &= 0xfc00;
		val16 |= tmrval;
		outw(val16, TCOv2_TMR(p));
		val16 = inw(TCOv2_TMR(p));
		spin_unlock(&p->io_lock);

		if ((val16 & 0x3ff) != tmrval)
			return -EINVAL;
	} else if (p->iTCO_version == 1) {
		spin_lock(&p->io_lock);
		val8 = inb(TCOv1_TMR(p));
		val8 &= 0xc0;
		val8 |= (tmrval & 0xff);
		outb(val8, TCOv1_TMR(p));
		val8 = inb(TCOv1_TMR(p));
		spin_unlock(&p->io_lock);

		if ((val8 & 0x3f) != tmrval)
			return -EINVAL;
	}

	wd_dev->timeout = t;
	return 0;
}