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
struct rtc_device {int irq_data; int /*<<< orphan*/  async_queue; int /*<<< orphan*/  irq_queue; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_IN ; 
 int RTC_IRQF ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void rtc_handle_legacy_irq(struct rtc_device *rtc, int num, int mode)
{
	unsigned long flags;

	/* mark one irq of the appropriate mode */
	spin_lock_irqsave(&rtc->irq_lock, flags);
	rtc->irq_data = (rtc->irq_data + (num << 8)) | (RTC_IRQF | mode);
	spin_unlock_irqrestore(&rtc->irq_lock, flags);

	wake_up_interruptible(&rtc->irq_queue);
	kill_fasync(&rtc->async_queue, SIGIO, POLL_IN);
}