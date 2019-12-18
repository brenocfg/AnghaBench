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
struct spear_rtc_config {int /*<<< orphan*/  lock; scalar_t__ ioaddr; } ;

/* Variables and functions */
 int STATUS_BUSY ; 
 scalar_t__ STATUS_REG ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rtc_wait_not_busy(struct spear_rtc_config *config)
{
	int status, count = 0;
	unsigned long flags;

	/* Assuming BUSY may stay active for 80 msec) */
	for (count = 0; count < 80; count++) {
		spin_lock_irqsave(&config->lock, flags);
		status = readl(config->ioaddr + STATUS_REG);
		spin_unlock_irqrestore(&config->lock, flags);
		if ((status & STATUS_BUSY) == 0)
			break;
		/* check status busy, after each msec */
		msleep(1);
	}
}