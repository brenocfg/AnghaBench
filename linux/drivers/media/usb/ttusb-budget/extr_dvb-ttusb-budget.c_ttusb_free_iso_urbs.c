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
struct ttusb {int /*<<< orphan*/  iso_buffer; int /*<<< orphan*/ * iso_urb; } ;

/* Variables and functions */
 int ISO_BUF_COUNT ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttusb_free_iso_urbs(struct ttusb *ttusb)
{
	int i;

	for (i = 0; i < ISO_BUF_COUNT; i++)
		usb_free_urb(ttusb->iso_urb[i]);
	kfree(ttusb->iso_buffer);
}