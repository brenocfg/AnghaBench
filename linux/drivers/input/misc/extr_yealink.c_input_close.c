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
struct yealink_dev {int shutdown; int /*<<< orphan*/  urb_irq; int /*<<< orphan*/  urb_ctl; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct yealink_dev* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void input_close(struct input_dev *dev)
{
	struct yealink_dev *yld = input_get_drvdata(dev);

	yld->shutdown = 1;
	/*
	 * Make sure the flag is seen by other CPUs before we start
	 * killing URBs so new URBs won't be submitted
	 */
	smp_wmb();

	usb_kill_urb(yld->urb_ctl);
	usb_kill_urb(yld->urb_irq);

	yld->shutdown = 0;
	smp_wmb();
}