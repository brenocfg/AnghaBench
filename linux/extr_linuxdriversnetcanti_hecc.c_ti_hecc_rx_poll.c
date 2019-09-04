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
struct ti_hecc_priv {scalar_t__ rx_next; int /*<<< orphan*/  mbx_lock; } ;
struct net_device {int dummy; } ;
struct napi_struct {struct net_device* dev; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int /*<<< orphan*/  HECC_CANME ; 
 int /*<<< orphan*/  HECC_CANMIM ; 
 int /*<<< orphan*/  HECC_CANRMP ; 
 int HECC_MAX_TX_MBOX ; 
 scalar_t__ HECC_RX_BUFFER_MBOX ; 
 int HECC_RX_FIRST_MBOX ; 
 int HECC_RX_HIGH_MBOX_MASK ; 
 int HECC_TX_MBOX_MASK ; 
 void* hecc_read (struct ti_hecc_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hecc_write (struct ti_hecc_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_complete (struct napi_struct*) ; 
 struct ti_hecc_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ ti_hecc_rx_pkt (struct ti_hecc_priv*,scalar_t__) ; 

__attribute__((used)) static int ti_hecc_rx_poll(struct napi_struct *napi, int quota)
{
	struct net_device *ndev = napi->dev;
	struct ti_hecc_priv *priv = netdev_priv(ndev);
	u32 num_pkts = 0;
	u32 mbx_mask;
	unsigned long pending_pkts, flags;

	if (!netif_running(ndev))
		return 0;

	while ((pending_pkts = hecc_read(priv, HECC_CANRMP)) &&
		num_pkts < quota) {
		mbx_mask = BIT(priv->rx_next); /* next rx mailbox to process */
		if (mbx_mask & pending_pkts) {
			if (ti_hecc_rx_pkt(priv, priv->rx_next) < 0)
				return num_pkts;
			++num_pkts;
		} else if (priv->rx_next > HECC_RX_BUFFER_MBOX) {
			break; /* pkt not received yet */
		}
		--priv->rx_next;
		if (priv->rx_next == HECC_RX_BUFFER_MBOX) {
			/* enable high bank mailboxes */
			spin_lock_irqsave(&priv->mbx_lock, flags);
			mbx_mask = hecc_read(priv, HECC_CANME);
			mbx_mask |= HECC_RX_HIGH_MBOX_MASK;
			hecc_write(priv, HECC_CANME, mbx_mask);
			spin_unlock_irqrestore(&priv->mbx_lock, flags);
		} else if (priv->rx_next == HECC_MAX_TX_MBOX - 1) {
			priv->rx_next = HECC_RX_FIRST_MBOX;
			break;
		}
	}

	/* Enable packet interrupt if all pkts are handled */
	if (hecc_read(priv, HECC_CANRMP) == 0) {
		napi_complete(napi);
		/* Re-enable RX mailbox interrupts */
		mbx_mask = hecc_read(priv, HECC_CANMIM);
		mbx_mask |= HECC_TX_MBOX_MASK;
		hecc_write(priv, HECC_CANMIM, mbx_mask);
	} else {
		/* repoll is done only if whole budget is used */
		num_pkts = quota;
	}

	return num_pkts;
}