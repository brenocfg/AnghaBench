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
struct usbnet {int dummy; } ;
struct usb_interface {int dummy; } ;
struct rndis_halt {void* msg_len; void* msg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_BUFFER_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RNDIS_MSG_HALT ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  kfree (struct rndis_halt*) ; 
 struct rndis_halt* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndis_command (struct usbnet*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbnet_cdc_unbind (struct usbnet*,struct usb_interface*) ; 

void rndis_unbind(struct usbnet *dev, struct usb_interface *intf)
{
	struct rndis_halt	*halt;

	/* try to clear any rndis state/activity (no i/o from stack!) */
	halt = kzalloc(CONTROL_BUFFER_SIZE, GFP_KERNEL);
	if (halt) {
		halt->msg_type = cpu_to_le32(RNDIS_MSG_HALT);
		halt->msg_len = cpu_to_le32(sizeof *halt);
		(void) rndis_command(dev, (void *)halt, CONTROL_BUFFER_SIZE);
		kfree(halt);
	}

	usbnet_cdc_unbind(dev, intf);
}