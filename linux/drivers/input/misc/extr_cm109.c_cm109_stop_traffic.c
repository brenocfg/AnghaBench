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
struct cm109_dev {int shutdown; int /*<<< orphan*/  urb_irq; int /*<<< orphan*/  urb_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  cm109_toggle_buzzer_sync (struct cm109_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cm109_stop_traffic(struct cm109_dev *dev)
{
	dev->shutdown = 1;
	/*
	 * Make sure other CPUs see this
	 */
	smp_wmb();

	usb_kill_urb(dev->urb_ctl);
	usb_kill_urb(dev->urb_irq);

	cm109_toggle_buzzer_sync(dev, 0);

	dev->shutdown = 0;
	smp_wmb();
}