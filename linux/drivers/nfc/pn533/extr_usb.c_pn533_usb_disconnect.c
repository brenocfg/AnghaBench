#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct pn533_usb_phy {int /*<<< orphan*/  ack_buffer; TYPE_1__* ack_urb; TYPE_1__* out_urb; TYPE_1__* in_urb; int /*<<< orphan*/  priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pn533_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 
 struct pn533_usb_phy* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pn533_usb_disconnect(struct usb_interface *interface)
{
	struct pn533_usb_phy *phy = usb_get_intfdata(interface);

	if (!phy)
		return;

	pn533_unregister_device(phy->priv);

	usb_set_intfdata(interface, NULL);

	usb_kill_urb(phy->in_urb);
	usb_kill_urb(phy->out_urb);
	usb_kill_urb(phy->ack_urb);

	kfree(phy->in_urb->transfer_buffer);
	usb_free_urb(phy->in_urb);
	usb_free_urb(phy->out_urb);
	usb_free_urb(phy->ack_urb);
	kfree(phy->ack_buffer);

	nfc_info(&interface->dev, "NXP PN533 NFC device disconnected\n");
}