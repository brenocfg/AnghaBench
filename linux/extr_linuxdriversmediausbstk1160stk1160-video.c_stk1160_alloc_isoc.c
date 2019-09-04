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
struct urb {int transfer_buffer_length; int interval; int number_of_packets; int transfer_flags; TYPE_1__* iso_frame_desc; scalar_t__ start_frame; struct stk1160* context; int /*<<< orphan*/  complete; scalar_t__ transfer_buffer; int /*<<< orphan*/  pipe; int /*<<< orphan*/  dev; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_4__ {int num_bufs; int max_pkt_size; struct urb** urb; scalar_t__* transfer_buffer; int /*<<< orphan*/ * buf; } ;
struct stk1160 {int max_pkt_size; TYPE_2__ isoc_ctl; int /*<<< orphan*/  udev; } ;
struct TYPE_3__ {int offset; int length; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STK1160_EP_VIDEO ; 
 int STK1160_MIN_BUFS ; 
 int STK1160_NUM_BUFS ; 
 int STK1160_NUM_PACKETS ; 
 int URB_ISO_ASAP ; 
 int URB_NO_TRANSFER_DMA_MAP ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct urb**) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stk1160_dbg (char*,...) ; 
 int /*<<< orphan*/  stk1160_err (char*,...) ; 
 int /*<<< orphan*/  stk1160_free_isoc (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_isoc_irq ; 
 int /*<<< orphan*/  stk1160_uninit_isoc (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_warn (char*,int) ; 
 scalar_t__ usb_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int stk1160_alloc_isoc(struct stk1160 *dev)
{
	struct urb *urb;
	int i, j, k, sb_size, max_packets, num_bufs;

	/*
	 * It may be necessary to release isoc here,
	 * since isoc are only released on disconnection.
	 * (see new_pkt_size flag)
	 */
	if (dev->isoc_ctl.num_bufs)
		stk1160_uninit_isoc(dev);

	stk1160_dbg("allocating urbs...\n");

	num_bufs = STK1160_NUM_BUFS;
	max_packets = STK1160_NUM_PACKETS;
	sb_size = max_packets * dev->max_pkt_size;

	dev->isoc_ctl.buf = NULL;
	dev->isoc_ctl.max_pkt_size = dev->max_pkt_size;
	dev->isoc_ctl.urb = kcalloc(num_bufs, sizeof(void *), GFP_KERNEL);
	if (!dev->isoc_ctl.urb) {
		stk1160_err("out of memory for urb array\n");
		return -ENOMEM;
	}

	dev->isoc_ctl.transfer_buffer = kcalloc(num_bufs, sizeof(void *),
						GFP_KERNEL);
	if (!dev->isoc_ctl.transfer_buffer) {
		stk1160_err("out of memory for usb transfers\n");
		kfree(dev->isoc_ctl.urb);
		return -ENOMEM;
	}

	/* allocate urbs and transfer buffers */
	for (i = 0; i < num_bufs; i++) {

		urb = usb_alloc_urb(max_packets, GFP_KERNEL);
		if (!urb)
			goto free_i_bufs;
		dev->isoc_ctl.urb[i] = urb;

#ifndef CONFIG_DMA_NONCOHERENT
		dev->isoc_ctl.transfer_buffer[i] = usb_alloc_coherent(dev->udev,
			sb_size, GFP_KERNEL, &urb->transfer_dma);
#else
		dev->isoc_ctl.transfer_buffer[i] = kmalloc(sb_size, GFP_KERNEL);
#endif
		if (!dev->isoc_ctl.transfer_buffer[i]) {
			stk1160_err("cannot alloc %d bytes for tx[%d] buffer\n",
				sb_size, i);

			/* Not enough transfer buffers, so just give up */
			if (i < STK1160_MIN_BUFS)
				goto free_i_bufs;
			goto nomore_tx_bufs;
		}
		memset(dev->isoc_ctl.transfer_buffer[i], 0, sb_size);

		/*
		 * FIXME: Where can I get the endpoint?
		 */
		urb->dev = dev->udev;
		urb->pipe = usb_rcvisocpipe(dev->udev, STK1160_EP_VIDEO);
		urb->transfer_buffer = dev->isoc_ctl.transfer_buffer[i];
		urb->transfer_buffer_length = sb_size;
		urb->complete = stk1160_isoc_irq;
		urb->context = dev;
		urb->interval = 1;
		urb->start_frame = 0;
		urb->number_of_packets = max_packets;
#ifndef CONFIG_DMA_NONCOHERENT
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
#else
		urb->transfer_flags = URB_ISO_ASAP;
#endif

		k = 0;
		for (j = 0; j < max_packets; j++) {
			urb->iso_frame_desc[j].offset = k;
			urb->iso_frame_desc[j].length =
					dev->isoc_ctl.max_pkt_size;
			k += dev->isoc_ctl.max_pkt_size;
		}
	}

	stk1160_dbg("%d urbs allocated\n", num_bufs);

	/* At last we can say we have some buffers */
	dev->isoc_ctl.num_bufs = num_bufs;

	return 0;

nomore_tx_bufs:
	/*
	 * Failed to allocate desired buffer count. However, we may have
	 * enough to work fine, so we just free the extra urb,
	 * store the allocated count and keep going, fingers crossed!
	 */
	usb_free_urb(dev->isoc_ctl.urb[i]);
	dev->isoc_ctl.urb[i] = NULL;

	stk1160_warn("%d urbs allocated. Trying to continue...\n", i - 1);

	dev->isoc_ctl.num_bufs = i - 1;

	return 0;

free_i_bufs:
	/* Save the allocated buffers so far, so we can properly free them */
	dev->isoc_ctl.num_bufs = i+1;
	stk1160_free_isoc(dev);
	return -ENOMEM;
}