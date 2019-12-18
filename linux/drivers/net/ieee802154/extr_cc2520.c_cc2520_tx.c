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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct ieee802154_hw {struct cc2520_private* priv; } ;
struct cc2520_private {int is_tx; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_complete; TYPE_1__* spi; scalar_t__ promiscuous; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC2520_CMD_SFLUSHTX ; 
 int /*<<< orphan*/  CC2520_CMD_SRXON ; 
 int /*<<< orphan*/  CC2520_CMD_STXONCCA ; 
 int CC2520_STATUS_TX_UNDERFLOW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int cc2520_cmd_strobe (struct cc2520_private*,int /*<<< orphan*/ ) ; 
 int cc2520_get_status (struct cc2520_private*,int*) ; 
 int cc2520_write_txfifo (struct cc2520_private*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crc_ccitt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cc2520_tx(struct ieee802154_hw *hw, struct sk_buff *skb)
{
	struct cc2520_private *priv = hw->priv;
	unsigned long flags;
	int rc;
	u8 status = 0;
	u8 pkt_len;

	/* In promiscuous mode we disable AUTOCRC so we can get the raw CRC
	 * values on RX. This means we need to manually add the CRC on TX.
	 */
	if (priv->promiscuous) {
		u16 crc = crc_ccitt(0, skb->data, skb->len);

		put_unaligned_le16(crc, skb_put(skb, 2));
		pkt_len = skb->len;
	} else {
		pkt_len = skb->len + 2;
	}

	rc = cc2520_cmd_strobe(priv, CC2520_CMD_SFLUSHTX);
	if (rc)
		goto err_tx;

	rc = cc2520_write_txfifo(priv, pkt_len, skb->data, skb->len);
	if (rc)
		goto err_tx;

	rc = cc2520_get_status(priv, &status);
	if (rc)
		goto err_tx;

	if (status & CC2520_STATUS_TX_UNDERFLOW) {
		dev_err(&priv->spi->dev, "cc2520 tx underflow exception\n");
		goto err_tx;
	}

	spin_lock_irqsave(&priv->lock, flags);
	WARN_ON(priv->is_tx);
	priv->is_tx = 1;
	spin_unlock_irqrestore(&priv->lock, flags);

	rc = cc2520_cmd_strobe(priv, CC2520_CMD_STXONCCA);
	if (rc)
		goto err;

	rc = wait_for_completion_interruptible(&priv->tx_complete);
	if (rc < 0)
		goto err;

	cc2520_cmd_strobe(priv, CC2520_CMD_SFLUSHTX);
	cc2520_cmd_strobe(priv, CC2520_CMD_SRXON);

	return rc;
err:
	spin_lock_irqsave(&priv->lock, flags);
	priv->is_tx = 0;
	spin_unlock_irqrestore(&priv->lock, flags);
err_tx:
	return rc;
}