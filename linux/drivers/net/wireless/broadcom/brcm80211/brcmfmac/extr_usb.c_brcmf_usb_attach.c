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
struct brcmf_usbdev {int nrxq; int ntxq; int /*<<< orphan*/  bus_mtu; int /*<<< orphan*/  state; struct brcmf_usbdev_info* devinfo; } ;
struct brcmf_usbdev_info {int rx_low_watermark; int tx_low_watermark; int tx_high_watermark; int tx_flowblock; int tx_freecount; struct brcmf_usbdev bus_pub; void* bulk_urb; void* ctl_urb; void* tx_reqs; int /*<<< orphan*/  tx_freeq; void* rx_reqs; int /*<<< orphan*/  rx_freeq; int /*<<< orphan*/  tx_postq; int /*<<< orphan*/  rx_postq; int /*<<< orphan*/  tx_flowblock_lock; int /*<<< orphan*/  qlock; int /*<<< orphan*/  ioctl_resp_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMFMAC_USB_STATE_DOWN ; 
 int /*<<< orphan*/  BRCMF_USB_MAX_PKT_SIZE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int /*<<< orphan*/  brcmf_usb_detach (struct brcmf_usbdev_info*) ; 
 void* brcmf_usbdev_qinit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
struct brcmf_usbdev *brcmf_usb_attach(struct brcmf_usbdev_info *devinfo,
				      int nrxq, int ntxq)
{
	brcmf_dbg(USB, "Enter\n");

	devinfo->bus_pub.nrxq = nrxq;
	devinfo->rx_low_watermark = nrxq / 2;
	devinfo->bus_pub.devinfo = devinfo;
	devinfo->bus_pub.ntxq = ntxq;
	devinfo->bus_pub.state = BRCMFMAC_USB_STATE_DOWN;

	/* flow control when too many tx urbs posted */
	devinfo->tx_low_watermark = ntxq / 4;
	devinfo->tx_high_watermark = devinfo->tx_low_watermark * 3;
	devinfo->bus_pub.bus_mtu = BRCMF_USB_MAX_PKT_SIZE;

	/* Initialize other structure content */
	init_waitqueue_head(&devinfo->ioctl_resp_wait);

	/* Initialize the spinlocks */
	spin_lock_init(&devinfo->qlock);
	spin_lock_init(&devinfo->tx_flowblock_lock);

	INIT_LIST_HEAD(&devinfo->rx_freeq);
	INIT_LIST_HEAD(&devinfo->rx_postq);

	INIT_LIST_HEAD(&devinfo->tx_freeq);
	INIT_LIST_HEAD(&devinfo->tx_postq);

	devinfo->tx_flowblock = false;

	devinfo->rx_reqs = brcmf_usbdev_qinit(&devinfo->rx_freeq, nrxq);
	if (!devinfo->rx_reqs)
		goto error;

	devinfo->tx_reqs = brcmf_usbdev_qinit(&devinfo->tx_freeq, ntxq);
	if (!devinfo->tx_reqs)
		goto error;
	devinfo->tx_freecount = ntxq;

	devinfo->ctl_urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!devinfo->ctl_urb)
		goto error;
	devinfo->bulk_urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!devinfo->bulk_urb)
		goto error;

	return &devinfo->bus_pub;

error:
	brcmf_err("failed!\n");
	brcmf_usb_detach(devinfo);
	return NULL;
}