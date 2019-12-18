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
struct chaoskey {int /*<<< orphan*/  interface; struct chaoskey* buf; struct chaoskey* name; int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct chaoskey*) ; 
 int /*<<< orphan*/  usb_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_intf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chaoskey_free(struct chaoskey *dev)
{
	if (dev) {
		usb_dbg(dev->interface, "free");
		usb_free_urb(dev->urb);
		kfree(dev->name);
		kfree(dev->buf);
		usb_put_intf(dev->interface);
		kfree(dev);
	}
}