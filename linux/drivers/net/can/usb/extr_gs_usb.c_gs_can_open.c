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
typedef  int u32 ;
struct urb {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct net_device {int dummy; } ;
struct gs_usb {int /*<<< orphan*/  rx_submitted; int /*<<< orphan*/  active_channels; } ;
struct gs_host_frame {int dummy; } ;
struct gs_device_mode {int /*<<< orphan*/  mode; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int ctrlmode; int /*<<< orphan*/  state; } ;
struct gs_can {TYPE_1__ can; int /*<<< orphan*/  channel; int /*<<< orphan*/  iface; int /*<<< orphan*/  netdev; int /*<<< orphan*/  udev; struct gs_usb* parent; } ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int CAN_CTRLMODE_ONE_SHOT ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GSUSB_ENDPOINT_IN ; 
 int /*<<< orphan*/  GS_CAN_MODE_LISTEN_ONLY ; 
 int /*<<< orphan*/  GS_CAN_MODE_LOOP_BACK ; 
 int /*<<< orphan*/  GS_CAN_MODE_ONE_SHOT ; 
 int /*<<< orphan*/  GS_CAN_MODE_START ; 
 int /*<<< orphan*/  GS_CAN_MODE_TRIPLE_SAMPLE ; 
 int GS_MAX_RX_URBS ; 
 int /*<<< orphan*/  GS_USB_BREQ_MODE ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_usb_receive_bulk_callback ; 
 int /*<<< orphan*/  interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gs_device_mode*) ; 
 struct gs_device_mode* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct gs_can* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int /*<<< orphan*/ * usb_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gs_device_mode*,int,int) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct gs_usb*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int gs_can_open(struct net_device *netdev)
{
	struct gs_can *dev = netdev_priv(netdev);
	struct gs_usb *parent = dev->parent;
	int rc, i;
	struct gs_device_mode *dm;
	u32 ctrlmode;

	rc = open_candev(netdev);
	if (rc)
		return rc;

	if (atomic_add_return(1, &parent->active_channels) == 1) {
		for (i = 0; i < GS_MAX_RX_URBS; i++) {
			struct urb *urb;
			u8 *buf;

			/* alloc rx urb */
			urb = usb_alloc_urb(0, GFP_KERNEL);
			if (!urb)
				return -ENOMEM;

			/* alloc rx buffer */
			buf = usb_alloc_coherent(dev->udev,
						 sizeof(struct gs_host_frame),
						 GFP_KERNEL,
						 &urb->transfer_dma);
			if (!buf) {
				netdev_err(netdev,
					   "No memory left for USB buffer\n");
				usb_free_urb(urb);
				return -ENOMEM;
			}

			/* fill, anchor, and submit rx urb */
			usb_fill_bulk_urb(urb,
					  dev->udev,
					  usb_rcvbulkpipe(dev->udev,
							  GSUSB_ENDPOINT_IN),
					  buf,
					  sizeof(struct gs_host_frame),
					  gs_usb_receive_bulk_callback,
					  parent);
			urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

			usb_anchor_urb(urb, &parent->rx_submitted);

			rc = usb_submit_urb(urb, GFP_KERNEL);
			if (rc) {
				if (rc == -ENODEV)
					netif_device_detach(dev->netdev);

				netdev_err(netdev,
					   "usb_submit failed (err=%d)\n",
					   rc);

				usb_unanchor_urb(urb);
				usb_free_urb(urb);
				break;
			}

			/* Drop reference,
			 * USB core will take care of freeing it
			 */
			usb_free_urb(urb);
		}
	}

	dm = kmalloc(sizeof(*dm), GFP_KERNEL);
	if (!dm)
		return -ENOMEM;

	/* flags */
	ctrlmode = dev->can.ctrlmode;
	dm->flags = 0;

	if (ctrlmode & CAN_CTRLMODE_LOOPBACK)
		dm->flags |= GS_CAN_MODE_LOOP_BACK;
	else if (ctrlmode & CAN_CTRLMODE_LISTENONLY)
		dm->flags |= GS_CAN_MODE_LISTEN_ONLY;

	/* Controller is not allowed to retry TX
	 * this mode is unavailable on atmels uc3c hardware
	 */
	if (ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		dm->flags |= GS_CAN_MODE_ONE_SHOT;

	if (ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		dm->flags |= GS_CAN_MODE_TRIPLE_SAMPLE;

	/* finally start device */
	dm->mode = GS_CAN_MODE_START;
	rc = usb_control_msg(interface_to_usbdev(dev->iface),
			     usb_sndctrlpipe(interface_to_usbdev(dev->iface), 0),
			     GS_USB_BREQ_MODE,
			     USB_DIR_OUT | USB_TYPE_VENDOR |
			     USB_RECIP_INTERFACE,
			     dev->channel,
			     0,
			     dm,
			     sizeof(*dm),
			     1000);

	if (rc < 0) {
		netdev_err(netdev, "Couldn't start device (err=%d)\n", rc);
		kfree(dm);
		return rc;
	}

	kfree(dm);

	dev->can.state = CAN_STATE_ERROR_ACTIVE;

	if (!(dev->can.ctrlmode & CAN_CTRLMODE_LISTENONLY))
		netif_start_queue(netdev);

	return 0;
}