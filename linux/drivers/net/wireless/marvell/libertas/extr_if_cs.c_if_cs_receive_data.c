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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct lbs_private {int /*<<< orphan*/  card; TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_CS_BIT_RX ; 
 int /*<<< orphan*/  IF_CS_HOST_INT_CAUSE ; 
 int /*<<< orphan*/  IF_CS_HOST_STATUS ; 
 int /*<<< orphan*/  IF_CS_READ ; 
 int /*<<< orphan*/  IF_CS_READ_LEN ; 
 int MRVDRV_ETH_RX_PACKET_BUFFER_SIZE ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int if_cs_read16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_cs_read16_rep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_cs_read8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_cs_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *if_cs_receive_data(struct lbs_private *priv)
{
	struct sk_buff *skb = NULL;
	u16 len;
	u8 *data;

	len = if_cs_read16(priv->card, IF_CS_READ_LEN);
	if (len == 0 || len > MRVDRV_ETH_RX_PACKET_BUFFER_SIZE) {
		netdev_err(priv->dev,
			   "card data buffer has invalid # of bytes (%d)\n",
			   len);
		priv->dev->stats.rx_dropped++;
		goto dat_err;
	}

	skb = dev_alloc_skb(MRVDRV_ETH_RX_PACKET_BUFFER_SIZE + 2);
	if (!skb)
		goto out;
	skb_put(skb, len);
	skb_reserve(skb, 2);/* 16 byte align */
	data = skb->data;

	/* read even number of bytes, then odd byte if necessary */
	if_cs_read16_rep(priv->card, IF_CS_READ, data, len/sizeof(u16));
	if (len & 1)
		data[len-1] = if_cs_read8(priv->card, IF_CS_READ);

dat_err:
	if_cs_write16(priv->card, IF_CS_HOST_STATUS, IF_CS_BIT_RX);
	if_cs_write16(priv->card, IF_CS_HOST_INT_CAUSE, IF_CS_BIT_RX);

out:
	return skb;
}