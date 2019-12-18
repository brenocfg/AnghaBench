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
struct rtc_device {unsigned long irq_data; int /*<<< orphan*/  irq_queue; } ;
struct file {struct rtc_device* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t rtc_dev_poll(struct file *file, poll_table *wait)
{
	struct rtc_device *rtc = file->private_data;
	unsigned long data;

	poll_wait(file, &rtc->irq_queue, wait);

	data = rtc->irq_data;

	return (data != 0) ? (EPOLLIN | EPOLLRDNORM) : 0;
}