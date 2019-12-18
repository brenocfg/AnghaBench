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
struct usbnet {int /*<<< orphan*/  net; } ;
struct usb_cdc_ncm_nth16 {scalar_t__ dwSignature; int /*<<< orphan*/  wNdpIndex; int /*<<< orphan*/  wSequence; int /*<<< orphan*/  wBlockLength; } ;
struct usb_cdc_ncm_ndp16 {int dummy; } ;
struct sk_buff {int len; scalar_t__ data; int /*<<< orphan*/  dev; } ;
struct cdc_ncm_ctx {int rx_max; int rx_seq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  USB_CDC_NCM_NTH16_SIGN ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 struct usbnet* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rx_err ; 

int cdc_ncm_rx_verify_nth16(struct cdc_ncm_ctx *ctx, struct sk_buff *skb_in)
{
	struct usbnet *dev = netdev_priv(skb_in->dev);
	struct usb_cdc_ncm_nth16 *nth16;
	int len;
	int ret = -EINVAL;

	if (ctx == NULL)
		goto error;

	if (skb_in->len < (sizeof(struct usb_cdc_ncm_nth16) +
					sizeof(struct usb_cdc_ncm_ndp16))) {
		netif_dbg(dev, rx_err, dev->net, "frame too short\n");
		goto error;
	}

	nth16 = (struct usb_cdc_ncm_nth16 *)skb_in->data;

	if (nth16->dwSignature != cpu_to_le32(USB_CDC_NCM_NTH16_SIGN)) {
		netif_dbg(dev, rx_err, dev->net,
			  "invalid NTH16 signature <%#010x>\n",
			  le32_to_cpu(nth16->dwSignature));
		goto error;
	}

	len = le16_to_cpu(nth16->wBlockLength);
	if (len > ctx->rx_max) {
		netif_dbg(dev, rx_err, dev->net,
			  "unsupported NTB block length %u/%u\n", len,
			  ctx->rx_max);
		goto error;
	}

	if ((ctx->rx_seq + 1) != le16_to_cpu(nth16->wSequence) &&
	    (ctx->rx_seq || le16_to_cpu(nth16->wSequence)) &&
	    !((ctx->rx_seq == 0xffff) && !le16_to_cpu(nth16->wSequence))) {
		netif_dbg(dev, rx_err, dev->net,
			  "sequence number glitch prev=%d curr=%d\n",
			  ctx->rx_seq, le16_to_cpu(nth16->wSequence));
	}
	ctx->rx_seq = le16_to_cpu(nth16->wSequence);

	ret = le16_to_cpu(nth16->wNdpIndex);
error:
	return ret;
}