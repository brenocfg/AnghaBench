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
struct zd_usb {int /*<<< orphan*/  intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_MEMCLEAR (struct zd_usb*,int) ; 
 int /*<<< orphan*/  usb_put_intf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void zd_usb_clear(struct zd_usb *usb)
{
	usb_set_intfdata(usb->intf, NULL);
	usb_put_intf(usb->intf);
	ZD_MEMCLEAR(usb, sizeof(*usb));
	/* FIXME: usb_interrupt, usb_tx, usb_rx? */
}