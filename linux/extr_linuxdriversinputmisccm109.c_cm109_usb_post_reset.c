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
struct cm109_dev {int /*<<< orphan*/  pm_mutex; scalar_t__ resetting; } ;

/* Variables and functions */
 int /*<<< orphan*/  cm109_restore_state (struct cm109_dev*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 struct cm109_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int cm109_usb_post_reset(struct usb_interface *intf)
{
	struct cm109_dev *dev = usb_get_intfdata(intf);

	dev->resetting = 0;
	smp_wmb();

	cm109_restore_state(dev);

	mutex_unlock(&dev->pm_mutex);

	return 0;
}