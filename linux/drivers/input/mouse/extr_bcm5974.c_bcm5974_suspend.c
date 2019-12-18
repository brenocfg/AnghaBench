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
struct bcm5974 {int /*<<< orphan*/  pm_mutex; scalar_t__ opened; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcm5974_pause_traffic (struct bcm5974*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bcm5974* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int bcm5974_suspend(struct usb_interface *iface, pm_message_t message)
{
	struct bcm5974 *dev = usb_get_intfdata(iface);

	mutex_lock(&dev->pm_mutex);

	if (dev->opened)
		bcm5974_pause_traffic(dev);

	mutex_unlock(&dev->pm_mutex);

	return 0;
}