#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct ems_usb {int free_slots; TYPE_1__ can; struct urb* intr_urb; scalar_t__* intr_in_buffer; int /*<<< orphan*/  udev; int /*<<< orphan*/  rx_submitted; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int CONTR_BUS_ERROR ; 
 int CONTR_CAN_MESSAGE ; 
 int CONTR_CAN_STATE ; 
 int CONTR_CONT_ON ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTR_IN_BUFFER_SIZE ; 
 int MAX_RX_URBS ; 
 int /*<<< orphan*/  RX_BUFFER_SIZE ; 
 int /*<<< orphan*/  SJA1000_MOD_NORMAL ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int ems_usb_control_cmd (struct ems_usb*,int) ; 
 int /*<<< orphan*/  ems_usb_read_bulk_callback ; 
 int /*<<< orphan*/  ems_usb_read_interrupt_callback ; 
 int ems_usb_write_mode (struct ems_usb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,...) ; 
 int /*<<< orphan*/ * usb_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ems_usb*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ems_usb*,int) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int ems_usb_start(struct ems_usb *dev)
{
	struct net_device *netdev = dev->netdev;
	int err, i;

	dev->intr_in_buffer[0] = 0;
	dev->free_slots = 50; /* initial size */

	for (i = 0; i < MAX_RX_URBS; i++) {
		struct urb *urb = NULL;
		u8 *buf = NULL;

		/* create a URB, and a buffer for it */
		urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!urb) {
			err = -ENOMEM;
			break;
		}

		buf = usb_alloc_coherent(dev->udev, RX_BUFFER_SIZE, GFP_KERNEL,
					 &urb->transfer_dma);
		if (!buf) {
			netdev_err(netdev, "No memory left for USB buffer\n");
			usb_free_urb(urb);
			err = -ENOMEM;
			break;
		}

		usb_fill_bulk_urb(urb, dev->udev, usb_rcvbulkpipe(dev->udev, 2),
				  buf, RX_BUFFER_SIZE,
				  ems_usb_read_bulk_callback, dev);
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		usb_anchor_urb(urb, &dev->rx_submitted);

		err = usb_submit_urb(urb, GFP_KERNEL);
		if (err) {
			usb_unanchor_urb(urb);
			usb_free_coherent(dev->udev, RX_BUFFER_SIZE, buf,
					  urb->transfer_dma);
			usb_free_urb(urb);
			break;
		}

		/* Drop reference, USB core will take care of freeing it */
		usb_free_urb(urb);
	}

	/* Did we submit any URBs */
	if (i == 0) {
		netdev_warn(netdev, "couldn't setup read URBs\n");
		return err;
	}

	/* Warn if we've couldn't transmit all the URBs */
	if (i < MAX_RX_URBS)
		netdev_warn(netdev, "rx performance may be slow\n");

	/* Setup and start interrupt URB */
	usb_fill_int_urb(dev->intr_urb, dev->udev,
			 usb_rcvintpipe(dev->udev, 1),
			 dev->intr_in_buffer,
			 INTR_IN_BUFFER_SIZE,
			 ems_usb_read_interrupt_callback, dev, 1);

	err = usb_submit_urb(dev->intr_urb, GFP_KERNEL);
	if (err) {
		netdev_warn(netdev, "intr URB submit failed: %d\n", err);

		return err;
	}

	/* CPC-USB will transfer received message to host */
	err = ems_usb_control_cmd(dev, CONTR_CAN_MESSAGE | CONTR_CONT_ON);
	if (err)
		goto failed;

	/* CPC-USB will transfer CAN state changes to host */
	err = ems_usb_control_cmd(dev, CONTR_CAN_STATE | CONTR_CONT_ON);
	if (err)
		goto failed;

	/* CPC-USB will transfer bus errors to host */
	err = ems_usb_control_cmd(dev, CONTR_BUS_ERROR | CONTR_CONT_ON);
	if (err)
		goto failed;

	err = ems_usb_write_mode(dev, SJA1000_MOD_NORMAL);
	if (err)
		goto failed;

	dev->can.state = CAN_STATE_ERROR_ACTIVE;

	return 0;

failed:
	netdev_warn(netdev, "couldn't submit control: %d\n", err);

	return err;
}