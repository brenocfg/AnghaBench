#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  bDebugOutEndpoint; int /*<<< orphan*/  bDebugInEndpoint; } ;
struct TYPE_15__ {TYPE_4__* gadget; TYPE_3__* serial; TYPE_2__* o_ep; TYPE_1__* i_ep; } ;
struct TYPE_14__ {int /*<<< orphan*/  bEndpointAddress; void* wMaxPacketSize; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {TYPE_2__* out; TYPE_1__* in; } ;
struct TYPE_11__ {TYPE_5__* desc; } ;
struct TYPE_10__ {TYPE_5__* desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  USB_DEBUG_MAX_PACKET_SIZE ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 TYPE_9__ dbg_desc ; 
 TYPE_8__ dbgp ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_5__ i_desc ; 
 TYPE_5__ o_desc ; 
 void* usb_ep_autoconfig (struct usb_gadget*,TYPE_5__*) ; 
 int /*<<< orphan*/  usb_ep_autoconfig_reset (struct usb_gadget*) ; 

__attribute__((used)) static int dbgp_configure_endpoints(struct usb_gadget *gadget)
{
	int stp;

	usb_ep_autoconfig_reset(gadget);

	dbgp.i_ep = usb_ep_autoconfig(gadget, &i_desc);
	if (!dbgp.i_ep) {
		stp = 1;
		goto fail_1;
	}

	i_desc.wMaxPacketSize =
		cpu_to_le16(USB_DEBUG_MAX_PACKET_SIZE);

	dbgp.o_ep = usb_ep_autoconfig(gadget, &o_desc);
	if (!dbgp.o_ep) {
		stp = 2;
		goto fail_1;
	}

	o_desc.wMaxPacketSize =
		cpu_to_le16(USB_DEBUG_MAX_PACKET_SIZE);

	dbg_desc.bDebugInEndpoint = i_desc.bEndpointAddress;
	dbg_desc.bDebugOutEndpoint = o_desc.bEndpointAddress;

#ifdef CONFIG_USB_G_DBGP_SERIAL
	dbgp.serial->in = dbgp.i_ep;
	dbgp.serial->out = dbgp.o_ep;

	dbgp.serial->in->desc = &i_desc;
	dbgp.serial->out->desc = &o_desc;
#endif

	return 0;

fail_1:
	dev_dbg(&dbgp.gadget->dev, "ep config: failure (%d)\n", stp);
	return -ENODEV;
}