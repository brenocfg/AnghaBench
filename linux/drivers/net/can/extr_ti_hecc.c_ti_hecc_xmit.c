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
struct ti_hecc_priv {int tx_head; int /*<<< orphan*/  mbx_lock; int /*<<< orphan*/  tx_tail; int /*<<< orphan*/  ndev; } ;
struct sk_buff {scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct can_frame {int can_dlc; int can_id; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int BIT (int) ; 
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_MASK ; 
 int /*<<< orphan*/  HECC_CANMCF ; 
 int HECC_CANMCF_RTR ; 
 int /*<<< orphan*/  HECC_CANMDH ; 
 int /*<<< orphan*/  HECC_CANMDL ; 
 int /*<<< orphan*/  HECC_CANME ; 
 int /*<<< orphan*/  HECC_CANMID ; 
 int HECC_CANMID_IDE ; 
 int /*<<< orphan*/  HECC_CANTRS ; 
 int HECC_TX_MASK ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,int) ; 
 int get_tx_head_mb (struct ti_hecc_priv*) ; 
 int get_tx_head_prio (struct ti_hecc_priv*) ; 
 int hecc_read (struct ti_hecc_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hecc_set_bit (struct ti_hecc_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hecc_write (struct ti_hecc_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hecc_write_mbx (struct ti_hecc_priv*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 struct ti_hecc_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t ti_hecc_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct ti_hecc_priv *priv = netdev_priv(ndev);
	struct can_frame *cf = (struct can_frame *)skb->data;
	u32 mbxno, mbx_mask, data;
	unsigned long flags;

	if (can_dropped_invalid_skb(ndev, skb))
		return NETDEV_TX_OK;

	mbxno = get_tx_head_mb(priv);
	mbx_mask = BIT(mbxno);
	spin_lock_irqsave(&priv->mbx_lock, flags);
	if (unlikely(hecc_read(priv, HECC_CANME) & mbx_mask)) {
		spin_unlock_irqrestore(&priv->mbx_lock, flags);
		netif_stop_queue(ndev);
		netdev_err(priv->ndev,
			   "BUG: TX mbx not ready tx_head=%08X, tx_tail=%08X\n",
			   priv->tx_head, priv->tx_tail);
		return NETDEV_TX_BUSY;
	}
	spin_unlock_irqrestore(&priv->mbx_lock, flags);

	/* Prepare mailbox for transmission */
	data = cf->can_dlc | (get_tx_head_prio(priv) << 8);
	if (cf->can_id & CAN_RTR_FLAG) /* Remote transmission request */
		data |= HECC_CANMCF_RTR;
	hecc_write_mbx(priv, mbxno, HECC_CANMCF, data);

	if (cf->can_id & CAN_EFF_FLAG) /* Extended frame format */
		data = (cf->can_id & CAN_EFF_MASK) | HECC_CANMID_IDE;
	else /* Standard frame format */
		data = (cf->can_id & CAN_SFF_MASK) << 18;
	hecc_write_mbx(priv, mbxno, HECC_CANMID, data);
	hecc_write_mbx(priv, mbxno, HECC_CANMDL,
		       be32_to_cpu(*(__be32 *)(cf->data)));
	if (cf->can_dlc > 4)
		hecc_write_mbx(priv, mbxno, HECC_CANMDH,
			       be32_to_cpu(*(__be32 *)(cf->data + 4)));
	else
		*(u32 *)(cf->data + 4) = 0;
	can_put_echo_skb(skb, ndev, mbxno);

	spin_lock_irqsave(&priv->mbx_lock, flags);
	--priv->tx_head;
	if ((hecc_read(priv, HECC_CANME) & BIT(get_tx_head_mb(priv))) ||
	    (priv->tx_head & HECC_TX_MASK) == HECC_TX_MASK) {
		netif_stop_queue(ndev);
	}
	hecc_set_bit(priv, HECC_CANME, mbx_mask);
	spin_unlock_irqrestore(&priv->mbx_lock, flags);

	hecc_write(priv, HECC_CANTRS, mbx_mask);

	return NETDEV_TX_OK;
}