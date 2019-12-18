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
typedef  int u8 ;
struct sk_buff {int* data; } ;
struct cc2520_private {TYPE_1__* spi; int /*<<< orphan*/  hw; int /*<<< orphan*/  promiscuous; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int IEEE802154_MTU ; 
 scalar_t__ cc2520_read_rxfifo (struct cc2520_private*,int*,int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  ieee802154_is_valid_psdu_len (int) ; 
 int /*<<< orphan*/  ieee802154_rx_irqsafe (int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int cc2520_rx(struct cc2520_private *priv)
{
	u8 len = 0, lqi = 0, bytes = 1;
	struct sk_buff *skb;

	/* Read single length byte from the radio. */
	cc2520_read_rxfifo(priv, &len, bytes);

	if (!ieee802154_is_valid_psdu_len(len)) {
		/* Corrupted frame received, clear frame buffer by
		 * reading entire buffer.
		 */
		dev_dbg(&priv->spi->dev, "corrupted frame received\n");
		len = IEEE802154_MTU;
	}

	skb = dev_alloc_skb(len);
	if (!skb)
		return -ENOMEM;

	if (cc2520_read_rxfifo(priv, skb_put(skb, len), len)) {
		dev_dbg(&priv->spi->dev, "frame reception failed\n");
		kfree_skb(skb);
		return -EINVAL;
	}

	/* In promiscuous mode, we configure the radio to include the
	 * CRC (AUTOCRC==0) and we pass on the packet unconditionally. If not
	 * in promiscuous mode, we check the CRC here, but leave the
	 * RSSI/LQI/CRC_OK bytes as they will get removed in the mac layer.
	 */
	if (!priv->promiscuous) {
		bool crc_ok;

		/* Check if the CRC is valid. With AUTOCRC set, the most
		 * significant bit of the last byte returned from the CC2520
		 * is CRC_OK flag. See section 20.3.4 of the datasheet.
		 */
		crc_ok = skb->data[len - 1] & BIT(7);

		/* If we failed CRC drop the packet in the driver layer. */
		if (!crc_ok) {
			dev_dbg(&priv->spi->dev, "CRC check failed\n");
			kfree_skb(skb);
			return -EINVAL;
		}

		/* To calculate LQI, the lower 7 bits of the last byte (the
		 * correlation value provided by the radio) must be scaled to
		 * the range 0-255. According to section 20.6, the correlation
		 * value ranges from 50-110. Ideally this would be calibrated
		 * per hardware design, but we use roughly the datasheet values
		 * to get close enough while avoiding floating point.
		 */
		lqi = skb->data[len - 1] & 0x7f;
		if (lqi < 50)
			lqi = 50;
		else if (lqi > 113)
			lqi = 113;
		lqi = (lqi - 50) * 4;
	}

	ieee802154_rx_irqsafe(priv->hw, skb, lqi);

	dev_vdbg(&priv->spi->dev, "RXFIFO: %x %x\n", len, lqi);

	return 0;
}