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
struct input_dev {int dummy; } ;
struct bcm5974 {int /*<<< orphan*/  intf; int /*<<< orphan*/  pm_mutex; scalar_t__ opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm5974_pause_traffic (struct bcm5974*) ; 
 struct bcm5974* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm5974_close(struct input_dev *input)
{
	struct bcm5974 *dev = input_get_drvdata(input);

	mutex_lock(&dev->pm_mutex);

	bcm5974_pause_traffic(dev);
	dev->opened = 0;

	mutex_unlock(&dev->pm_mutex);

	usb_autopm_put_interface(dev->intf);
}