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
struct urb {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct hif_device_usb {int /*<<< orphan*/  rx_submitted; int /*<<< orphan*/  udev; int /*<<< orphan*/  rx_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_RX_BUF_SIZE ; 
 int MAX_RX_URB_NUM ; 
 int /*<<< orphan*/  USB_WLAN_RX_PIPE ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hif_usb_dealloc_rx_urbs (struct hif_device_usb*) ; 
 int /*<<< orphan*/  ath9k_hif_usb_rx_cb ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int ath9k_hif_usb_alloc_rx_urbs(struct hif_device_usb *hif_dev)
{
	struct urb *urb = NULL;
	struct sk_buff *skb = NULL;
	int i, ret;

	init_usb_anchor(&hif_dev->rx_submitted);
	spin_lock_init(&hif_dev->rx_lock);

	for (i = 0; i < MAX_RX_URB_NUM; i++) {

		/* Allocate URB */
		urb = usb_alloc_urb(0, GFP_KERNEL);
		if (urb == NULL) {
			ret = -ENOMEM;
			goto err_urb;
		}

		/* Allocate buffer */
		skb = alloc_skb(MAX_RX_BUF_SIZE, GFP_KERNEL);
		if (!skb) {
			ret = -ENOMEM;
			goto err_skb;
		}

		usb_fill_bulk_urb(urb, hif_dev->udev,
				  usb_rcvbulkpipe(hif_dev->udev,
						  USB_WLAN_RX_PIPE),
				  skb->data, MAX_RX_BUF_SIZE,
				  ath9k_hif_usb_rx_cb, skb);

		/* Anchor URB */
		usb_anchor_urb(urb, &hif_dev->rx_submitted);

		/* Submit URB */
		ret = usb_submit_urb(urb, GFP_KERNEL);
		if (ret) {
			usb_unanchor_urb(urb);
			goto err_submit;
		}

		/*
		 * Drop reference count.
		 * This ensures that the URB is freed when killing them.
		 */
		usb_free_urb(urb);
	}

	return 0;

err_submit:
	kfree_skb(skb);
err_skb:
	usb_free_urb(urb);
err_urb:
	ath9k_hif_usb_dealloc_rx_urbs(hif_dev);
	return ret;
}