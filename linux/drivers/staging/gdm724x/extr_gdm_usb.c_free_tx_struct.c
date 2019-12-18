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
struct usb_tx {struct usb_tx* buf; int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usb_tx*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_tx_struct(struct usb_tx *t)
{
	if (t) {
		usb_free_urb(t->urb);
		kfree(t->buf);
		kfree(t);
	}
}