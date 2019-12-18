#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/  rx_tl; int /*<<< orphan*/  net; int /*<<< orphan*/  rx_urb; TYPE_4__* rx_skb; int /*<<< orphan*/  usb; } ;
typedef  TYPE_1__ pegasus_t ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PEGASUS_MTU ; 
 int PEGASUS_RX_URB_FAIL ; 
 int PEGASUS_UNPLUG ; 
 TYPE_4__* __netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_warn (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  read_bulk_callback ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_fixup(unsigned long data)
{
	pegasus_t *pegasus;
	int status;

	pegasus = (pegasus_t *) data;
	if (pegasus->flags & PEGASUS_UNPLUG)
		return;

	if (pegasus->flags & PEGASUS_RX_URB_FAIL)
		if (pegasus->rx_skb)
			goto try_again;
	if (pegasus->rx_skb == NULL)
		pegasus->rx_skb = __netdev_alloc_skb_ip_align(pegasus->net,
							      PEGASUS_MTU,
							      GFP_ATOMIC);
	if (pegasus->rx_skb == NULL) {
		netif_warn(pegasus, rx_err, pegasus->net, "low on memory\n");
		tasklet_schedule(&pegasus->rx_tl);
		return;
	}
	usb_fill_bulk_urb(pegasus->rx_urb, pegasus->usb,
			  usb_rcvbulkpipe(pegasus->usb, 1),
			  pegasus->rx_skb->data, PEGASUS_MTU,
			  read_bulk_callback, pegasus);
try_again:
	status = usb_submit_urb(pegasus->rx_urb, GFP_ATOMIC);
	if (status == -ENODEV)
		netif_device_detach(pegasus->net);
	else if (status) {
		pegasus->flags |= PEGASUS_RX_URB_FAIL;
		tasklet_schedule(&pegasus->rx_tl);
	} else {
		pegasus->flags &= ~PEGASUS_RX_URB_FAIL;
	}
}