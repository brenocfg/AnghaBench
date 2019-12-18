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
struct sk_buff {scalar_t__ len; int* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_fifo_errors; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DM_RX_OVERHEAD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dm9601_rx_fixup(struct usbnet *dev, struct sk_buff *skb)
{
	u8 status;
	int len;

	/* format:
	   b1: rx status
	   b2: packet length (incl crc) low
	   b3: packet length (incl crc) high
	   b4..n-4: packet data
	   bn-3..bn: ethernet crc
	 */

	if (unlikely(skb->len < DM_RX_OVERHEAD)) {
		dev_err(&dev->udev->dev, "unexpected tiny rx frame\n");
		return 0;
	}

	status = skb->data[0];
	len = (skb->data[1] | (skb->data[2] << 8)) - 4;

	if (unlikely(status & 0xbf)) {
		if (status & 0x01) dev->net->stats.rx_fifo_errors++;
		if (status & 0x02) dev->net->stats.rx_crc_errors++;
		if (status & 0x04) dev->net->stats.rx_frame_errors++;
		if (status & 0x20) dev->net->stats.rx_missed_errors++;
		if (status & 0x90) dev->net->stats.rx_length_errors++;
		return 0;
	}

	skb_pull(skb, 3);
	skb_trim(skb, len);

	return 1;
}