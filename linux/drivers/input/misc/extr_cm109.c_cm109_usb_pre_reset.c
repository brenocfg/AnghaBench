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
struct usb_interface {int dummy; } ;
struct cm109_dev {int resetting; int /*<<< orphan*/  pm_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  cm109_stop_traffic (struct cm109_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 struct cm109_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int cm109_usb_pre_reset(struct usb_interface *intf)
{
	struct cm109_dev *dev = usb_get_intfdata(intf);

	mutex_lock(&dev->pm_mutex);

	/*
	 * Make sure input events don't try to toggle buzzer
	 * while we are resetting
	 */
	dev->resetting = 1;
	smp_wmb();

	cm109_stop_traffic(dev);

	return 0;
}