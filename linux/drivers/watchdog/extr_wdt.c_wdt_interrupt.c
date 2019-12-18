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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned char WDC_SR_FANGOOD ; 
 unsigned char WDC_SR_WCCR ; 
 int /*<<< orphan*/  WDT_SR ; 
 int /*<<< orphan*/  emergency_restart () ; 
 unsigned char inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_crit (char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tachometer ; 
 int type ; 
 int /*<<< orphan*/  wdt_decode_501 (unsigned char) ; 
 int /*<<< orphan*/  wdt_lock ; 

__attribute__((used)) static irqreturn_t wdt_interrupt(int irq, void *dev_id)
{
	/*
	 *	Read the status register see what is up and
	 *	then printk it.
	 */
	unsigned char status;

	spin_lock(&wdt_lock);
	status = inb_p(WDT_SR);

	pr_crit("WDT status %d\n", status);

	if (type == 501) {
		wdt_decode_501(status);
		if (tachometer) {
			if (!(status & WDC_SR_FANGOOD))
				pr_crit("Possible fan fault\n");
		}
	}
	if (!(status & WDC_SR_WCCR)) {
#ifdef SOFTWARE_REBOOT
#ifdef ONLY_TESTING
		pr_crit("Would Reboot\n");
#else
		pr_crit("Initiating system reboot\n");
		emergency_restart();
#endif
#else
		pr_crit("Reset in 5ms\n");
#endif
	}
	spin_unlock(&wdt_lock);
	return IRQ_HANDLED;
}