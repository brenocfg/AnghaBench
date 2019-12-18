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
typedef  int u32 ;
struct usbnet {int /*<<< orphan*/  net; scalar_t__* data; } ;
struct usb_cdc_ncm_ndp16 {scalar_t__ dwSignature; int /*<<< orphan*/  wNextNdpIndex; struct usb_cdc_ncm_dpe16* dpe16; } ;
struct usb_cdc_ncm_dpe16 {int /*<<< orphan*/  wDatagramLength; int /*<<< orphan*/  wDatagramIndex; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct cdc_ncm_ctx {int rx_max; int /*<<< orphan*/  rx_ntbs; int /*<<< orphan*/  rx_overhead; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 int /*<<< orphan*/  USB_CDC_NCM_NDP16_NOCRC_SIGN ; 
 int cdc_ncm_rx_verify_ndp16 (struct sk_buff*,int) ; 
 int cdc_ncm_rx_verify_nth16 (struct cdc_ncm_ctx*,struct sk_buff*) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,scalar_t__,int) ; 
 int /*<<< orphan*/  usbnet_skb_return (struct usbnet*,struct sk_buff*) ; 

int cdc_ncm_rx_fixup(struct usbnet *dev, struct sk_buff *skb_in)
{
	struct sk_buff *skb;
	struct cdc_ncm_ctx *ctx = (struct cdc_ncm_ctx *)dev->data[0];
	int len;
	int nframes;
	int x;
	int offset;
	struct usb_cdc_ncm_ndp16 *ndp16;
	struct usb_cdc_ncm_dpe16 *dpe16;
	int ndpoffset;
	int loopcount = 50; /* arbitrary max preventing infinite loop */
	u32 payload = 0;

	ndpoffset = cdc_ncm_rx_verify_nth16(ctx, skb_in);
	if (ndpoffset < 0)
		goto error;

next_ndp:
	nframes = cdc_ncm_rx_verify_ndp16(skb_in, ndpoffset);
	if (nframes < 0)
		goto error;

	ndp16 = (struct usb_cdc_ncm_ndp16 *)(skb_in->data + ndpoffset);

	if (ndp16->dwSignature != cpu_to_le32(USB_CDC_NCM_NDP16_NOCRC_SIGN)) {
		netif_dbg(dev, rx_err, dev->net,
			  "invalid DPT16 signature <%#010x>\n",
			  le32_to_cpu(ndp16->dwSignature));
		goto err_ndp;
	}
	dpe16 = ndp16->dpe16;

	for (x = 0; x < nframes; x++, dpe16++) {
		offset = le16_to_cpu(dpe16->wDatagramIndex);
		len = le16_to_cpu(dpe16->wDatagramLength);

		/*
		 * CDC NCM ch. 3.7
		 * All entries after first NULL entry are to be ignored
		 */
		if ((offset == 0) || (len == 0)) {
			if (!x)
				goto err_ndp; /* empty NTB */
			break;
		}

		/* sanity checking */
		if (((offset + len) > skb_in->len) ||
				(len > ctx->rx_max) || (len < ETH_HLEN)) {
			netif_dbg(dev, rx_err, dev->net,
				  "invalid frame detected (ignored) offset[%u]=%u, length=%u, skb=%p\n",
				  x, offset, len, skb_in);
			if (!x)
				goto err_ndp;
			break;

		} else {
			/* create a fresh copy to reduce truesize */
			skb = netdev_alloc_skb_ip_align(dev->net,  len);
			if (!skb)
				goto error;
			skb_put_data(skb, skb_in->data + offset, len);
			usbnet_skb_return(dev, skb);
			payload += len;	/* count payload bytes in this NTB */
		}
	}
err_ndp:
	/* are there more NDPs to process? */
	ndpoffset = le16_to_cpu(ndp16->wNextNdpIndex);
	if (ndpoffset && loopcount--)
		goto next_ndp;

	/* update stats */
	ctx->rx_overhead += skb_in->len - payload;
	ctx->rx_ntbs++;

	return 1;
error:
	return 0;
}