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
struct pegasus {int is_open; int /*<<< orphan*/  intf; int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  init; int /*<<< orphan*/  irq; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct pegasus* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pegasus_close(struct input_dev *dev)
{
	struct pegasus *pegasus = input_get_drvdata(dev);

	mutex_lock(&pegasus->pm_mutex);
	usb_kill_urb(pegasus->irq);
	cancel_work_sync(&pegasus->init);
	pegasus->is_open = false;
	mutex_unlock(&pegasus->pm_mutex);

	usb_autopm_put_interface(pegasus->intf);
}