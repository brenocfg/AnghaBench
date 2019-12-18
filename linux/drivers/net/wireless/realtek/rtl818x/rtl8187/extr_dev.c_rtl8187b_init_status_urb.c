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
struct urb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct rtl8187_priv {int /*<<< orphan*/  anchored; TYPE_1__ b_tx_status; int /*<<< orphan*/  udev; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  rtl8187b_status_cb ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct ieee80211_hw*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int rtl8187b_init_status_urb(struct ieee80211_hw *dev)
{
	struct rtl8187_priv *priv = dev->priv;
	struct urb *entry;
	int ret = 0;

	entry = usb_alloc_urb(0, GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	usb_fill_bulk_urb(entry, priv->udev, usb_rcvbulkpipe(priv->udev, 9),
			  &priv->b_tx_status.buf, sizeof(priv->b_tx_status.buf),
			  rtl8187b_status_cb, dev);

	usb_anchor_urb(entry, &priv->anchored);
	ret = usb_submit_urb(entry, GFP_KERNEL);
	if (ret)
		usb_unanchor_urb(entry);
	usb_free_urb(entry);

	return ret;
}