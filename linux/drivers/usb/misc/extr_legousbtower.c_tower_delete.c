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
struct lego_usb_tower {int /*<<< orphan*/  udev; struct lego_usb_tower* interrupt_out_buffer; struct lego_usb_tower* interrupt_in_buffer; struct lego_usb_tower* read_buffer; int /*<<< orphan*/  interrupt_out_urb; int /*<<< orphan*/  interrupt_in_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct lego_usb_tower*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tower_delete (struct lego_usb_tower *dev)
{
	/* free data structures */
	usb_free_urb(dev->interrupt_in_urb);
	usb_free_urb(dev->interrupt_out_urb);
	kfree (dev->read_buffer);
	kfree (dev->interrupt_in_buffer);
	kfree (dev->interrupt_out_buffer);
	usb_put_dev(dev->udev);
	kfree (dev);
}