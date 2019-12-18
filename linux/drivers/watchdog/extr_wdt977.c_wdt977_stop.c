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
 int DEVICE_REGISTER ; 
 int /*<<< orphan*/  IO_DATA_PORT ; 
 int /*<<< orphan*/  IO_INDEX_PORT ; 
 int LOCK_DATA ; 
 int UNLOCK_DATA ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spinlock ; 

__attribute__((used)) static int wdt977_stop(void)
{
	unsigned long flags;
	spin_lock_irqsave(&spinlock, flags);

	/* unlock the SuperIO chip */
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);

	/* select device Aux2 (device=8) and set watchdog regs F2,F3 and F4
	* F3 is reset to its default state
	* F4 can clear the TIMEOUT'ed state (bit 0) - back to default
	* We can not use GP17 as a PowerLed, as we use its usage as a RedLed
	*/
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);
	outb_p(0xF2, IO_INDEX_PORT);
	outb_p(0xFF, IO_DATA_PORT);
	outb_p(0xF3, IO_INDEX_PORT);
	outb_p(0x00, IO_DATA_PORT);
	outb_p(0xF4, IO_INDEX_PORT);
	outb_p(0x00, IO_DATA_PORT);
	outb_p(0xF2, IO_INDEX_PORT);
	outb_p(0x00, IO_DATA_PORT);

	/* at last select device Aux1 (dev=7) and set
	   GP16 as a watchdog output */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x07, IO_DATA_PORT);
	outb_p(0xE6, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);

	/* lock the SuperIO chip */
	outb_p(LOCK_DATA, IO_INDEX_PORT);

	spin_unlock_irqrestore(&spinlock, flags);
	pr_info("shutdown\n");

	return 0;
}