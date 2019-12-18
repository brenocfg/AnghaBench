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

/* Variables and functions */
 int /*<<< orphan*/  WDT_RT ; 
 unsigned short inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wdtpci_lock ; 

__attribute__((used)) static int wdtpci_get_temperature(int *temperature)
{
	unsigned short c;
	unsigned long flags;
	spin_lock_irqsave(&wdtpci_lock, flags);
	c = inb(WDT_RT);
	udelay(8);
	spin_unlock_irqrestore(&wdtpci_lock, flags);
	*temperature = (c * 11 / 15) + 7;
	return 0;
}