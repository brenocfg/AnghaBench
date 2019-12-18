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
struct rtc_device {int /*<<< orphan*/  flags; } ;
struct inode {int dummy; } ;
struct file {struct rtc_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_DEV_BUSY ; 
 int /*<<< orphan*/  RTC_UIE_OFF ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_dev_ioctl (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_irq_set_state (struct rtc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq_enable (struct rtc_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtc_dev_release(struct inode *inode, struct file *file)
{
	struct rtc_device *rtc = file->private_data;

	/* We shut down the repeating IRQs that userspace enabled,
	 * since nothing is listening to them.
	 *  - Update (UIE) ... currently only managed through ioctls
	 *  - Periodic (PIE) ... also used through rtc_*() interface calls
	 *
	 * Leave the alarm alone; it may be set to trigger a system wakeup
	 * later, or be used by kernel code, and is a one-shot event anyway.
	 */

	/* Keep ioctl until all drivers are converted */
	rtc_dev_ioctl(file, RTC_UIE_OFF, 0);
	rtc_update_irq_enable(rtc, 0);
	rtc_irq_set_state(rtc, 0);

	clear_bit_unlock(RTC_DEV_BUSY, &rtc->flags);
	return 0;
}