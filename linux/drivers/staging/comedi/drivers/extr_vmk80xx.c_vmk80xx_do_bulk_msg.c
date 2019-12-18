#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmk80xx_private {int /*<<< orphan*/  usb_rx_buf; TYPE_2__* ep_tx; int /*<<< orphan*/  usb_tx_buf; TYPE_1__* ep_rx; } ;
struct usb_device {int dummy; } ;
struct comedi_device {struct vmk80xx_private* private; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_4__ {int bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_3__ {int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int HZ ; 
 struct usb_device* comedi_to_usb_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  usb_bulk_msg (struct usb_device*,unsigned int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int) ; 
 size_t usb_endpoint_maxp (TYPE_2__*) ; 
 unsigned int usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmk80xx_do_bulk_msg(struct comedi_device *dev)
{
	struct vmk80xx_private *devpriv = dev->private;
	struct usb_device *usb = comedi_to_usb_dev(dev);
	__u8 tx_addr;
	__u8 rx_addr;
	unsigned int tx_pipe;
	unsigned int rx_pipe;
	size_t size;

	tx_addr = devpriv->ep_tx->bEndpointAddress;
	rx_addr = devpriv->ep_rx->bEndpointAddress;
	tx_pipe = usb_sndbulkpipe(usb, tx_addr);
	rx_pipe = usb_rcvbulkpipe(usb, rx_addr);

	/*
	 * The max packet size attributes of the K8061
	 * input/output endpoints are identical
	 */
	size = usb_endpoint_maxp(devpriv->ep_tx);

	usb_bulk_msg(usb, tx_pipe, devpriv->usb_tx_buf,
		     size, NULL, devpriv->ep_tx->bInterval);
	usb_bulk_msg(usb, rx_pipe, devpriv->usb_rx_buf, size, NULL, HZ * 10);
}