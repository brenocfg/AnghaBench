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
struct u2fzero_device {int present; int /*<<< orphan*/  urb; int /*<<< orphan*/  lock; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 struct u2fzero_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_poison_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void u2fzero_remove(struct hid_device *hdev)
{
	struct u2fzero_device *dev = hid_get_drvdata(hdev);

	mutex_lock(&dev->lock);
	dev->present = false;
	mutex_unlock(&dev->lock);

	hid_hw_stop(hdev);
	usb_poison_urb(dev->urb);
	usb_free_urb(dev->urb);
}