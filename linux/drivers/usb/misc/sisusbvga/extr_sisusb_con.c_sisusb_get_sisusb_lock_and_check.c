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
struct sisusb_usb_data {int /*<<< orphan*/  lock; int /*<<< orphan*/ * havethisconsole; } ;

/* Variables and functions */
 scalar_t__ in_atomic () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sisusb_usb_data* sisusb_get_sisusb (unsigned short) ; 
 int /*<<< orphan*/  sisusb_sisusb_valid (struct sisusb_usb_data*) ; 

__attribute__((used)) static struct sisusb_usb_data *
sisusb_get_sisusb_lock_and_check(unsigned short console)
{
	struct sisusb_usb_data *sisusb;

	/* We can't handle console calls in non-schedulable
	 * context due to our locks and the USB transport.
	 * So we simply ignore them. This should only affect
	 * some calls to printk.
	 */
	if (in_atomic())
		return NULL;

	sisusb = sisusb_get_sisusb(console);
	if (!sisusb)
		return NULL;

	mutex_lock(&sisusb->lock);

	if (!sisusb_sisusb_valid(sisusb) ||
	    !sisusb->havethisconsole[console]) {
		mutex_unlock(&sisusb->lock);
		return NULL;
	}

	return sisusb;
}