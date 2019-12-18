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
struct ttusb {scalar_t__ iso_streaming; int /*<<< orphan*/ * iso_urb; } ;

/* Variables and functions */
 int ISO_BUF_COUNT ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttusb_stop_iso_xfer(struct ttusb *ttusb)
{
	int i;

	for (i = 0; i < ISO_BUF_COUNT; i++)
		usb_kill_urb(ttusb->iso_urb[i]);

	ttusb->iso_streaming = 0;
}