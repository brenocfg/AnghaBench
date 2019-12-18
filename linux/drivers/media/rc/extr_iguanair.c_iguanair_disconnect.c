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
struct usb_interface {int dummy; } ;
struct iguanair {int /*<<< orphan*/  dma_out; int /*<<< orphan*/  packet; int /*<<< orphan*/  udev; int /*<<< orphan*/  dma_in; int /*<<< orphan*/  buf_in; int /*<<< orphan*/  urb_out; int /*<<< orphan*/  urb_in; int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_IN_PACKET ; 
 int /*<<< orphan*/  MAX_OUT_PACKET ; 
 int /*<<< orphan*/  kfree (struct iguanair*) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct iguanair* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iguanair_disconnect(struct usb_interface *intf)
{
	struct iguanair *ir = usb_get_intfdata(intf);

	rc_unregister_device(ir->rc);
	usb_set_intfdata(intf, NULL);
	usb_kill_urb(ir->urb_in);
	usb_kill_urb(ir->urb_out);
	usb_free_urb(ir->urb_in);
	usb_free_urb(ir->urb_out);
	usb_free_coherent(ir->udev, MAX_IN_PACKET, ir->buf_in, ir->dma_in);
	usb_free_coherent(ir->udev, MAX_OUT_PACKET, ir->packet, ir->dma_out);
	kfree(ir);
}