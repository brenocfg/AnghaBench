#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct usbnet {TYPE_3__* net; TYPE_1__* udev; } ;
struct sk_buff {int len; int* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; } ;
struct TYPE_6__ {int hard_header_len; TYPE_2__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MCS7830_RX_ALIGNMENT_ERROR ; 
 int MCS7830_RX_CRC_ERROR ; 
 int MCS7830_RX_FRAME_CORRECT ; 
 int MCS7830_RX_LARGE_FRAME ; 
 int MCS7830_RX_LENGTH_ERROR ; 
 int MCS7830_RX_SHORT_FRAME ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static int mcs7830_rx_fixup(struct usbnet *dev, struct sk_buff *skb)
{
	u8 status;

	/* This check is no longer done by usbnet */
	if (skb->len < dev->net->hard_header_len) {
		dev_err(&dev->udev->dev, "unexpected tiny rx frame\n");
		return 0;
	}

	skb_trim(skb, skb->len - 1);
	status = skb->data[skb->len];

	if (status != MCS7830_RX_FRAME_CORRECT) {
		dev_dbg(&dev->udev->dev, "rx fixup status %x\n", status);

		/* hmm, perhaps usbnet.c already sees a globally visible
		   frame error and increments rx_errors on its own already? */
		dev->net->stats.rx_errors++;

		if (status &	(MCS7830_RX_SHORT_FRAME
				|MCS7830_RX_LENGTH_ERROR
				|MCS7830_RX_LARGE_FRAME))
			dev->net->stats.rx_length_errors++;
		if (status & MCS7830_RX_ALIGNMENT_ERROR)
			dev->net->stats.rx_frame_errors++;
		if (status & MCS7830_RX_CRC_ERROR)
			dev->net->stats.rx_crc_errors++;
	}

	return skb->len > 0;
}