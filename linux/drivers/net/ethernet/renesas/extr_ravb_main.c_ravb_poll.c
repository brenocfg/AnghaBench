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
typedef  int u32 ;
struct ravb_private {scalar_t__ chip_id; scalar_t__ rx_over_errors; scalar_t__ rx_fifo_errors; TYPE_1__* stats; int /*<<< orphan*/  lock; struct napi_struct* napi; } ;
struct TYPE_4__ {scalar_t__ rx_over_errors; scalar_t__ rx_fifo_errors; } ;
struct net_device {TYPE_2__ stats; } ;
struct napi_struct {struct net_device* dev; } ;
struct TYPE_3__ {scalar_t__ rx_over_errors; } ;

/* Variables and functions */
 int BIT (int) ; 
 size_t RAVB_BE ; 
 size_t RAVB_NC ; 
 scalar_t__ RCAR_GEN2 ; 
 int /*<<< orphan*/  RIC0 ; 
 int /*<<< orphan*/  RIE0 ; 
 int /*<<< orphan*/  RIS0 ; 
 int RIS0_RESERVED ; 
 int /*<<< orphan*/  TIC ; 
 int /*<<< orphan*/  TIE ; 
 int /*<<< orphan*/  TIS ; 
 int TIS_RESERVED ; 
 int /*<<< orphan*/  napi_complete (struct napi_struct*) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_subqueue (struct net_device*,int) ; 
 int /*<<< orphan*/  ravb_modify (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int ravb_read (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ ravb_rx (struct net_device*,int*,int) ; 
 int /*<<< orphan*/  ravb_tx_free (struct net_device*,int,int) ; 
 int /*<<< orphan*/  ravb_write (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ravb_poll(struct napi_struct *napi, int budget)
{
	struct net_device *ndev = napi->dev;
	struct ravb_private *priv = netdev_priv(ndev);
	unsigned long flags;
	int q = napi - priv->napi;
	int mask = BIT(q);
	int quota = budget;
	u32 ris0, tis;

	for (;;) {
		tis = ravb_read(ndev, TIS);
		ris0 = ravb_read(ndev, RIS0);
		if (!((ris0 & mask) || (tis & mask)))
			break;

		/* Processing RX Descriptor Ring */
		if (ris0 & mask) {
			/* Clear RX interrupt */
			ravb_write(ndev, ~(mask | RIS0_RESERVED), RIS0);
			if (ravb_rx(ndev, &quota, q))
				goto out;
		}
		/* Processing TX Descriptor Ring */
		if (tis & mask) {
			spin_lock_irqsave(&priv->lock, flags);
			/* Clear TX interrupt */
			ravb_write(ndev, ~(mask | TIS_RESERVED), TIS);
			ravb_tx_free(ndev, q, true);
			netif_wake_subqueue(ndev, q);
			spin_unlock_irqrestore(&priv->lock, flags);
		}
	}

	napi_complete(napi);

	/* Re-enable RX/TX interrupts */
	spin_lock_irqsave(&priv->lock, flags);
	if (priv->chip_id == RCAR_GEN2) {
		ravb_modify(ndev, RIC0, mask, mask);
		ravb_modify(ndev, TIC,  mask, mask);
	} else {
		ravb_write(ndev, mask, RIE0);
		ravb_write(ndev, mask, TIE);
	}
	spin_unlock_irqrestore(&priv->lock, flags);

	/* Receive error message handling */
	priv->rx_over_errors =  priv->stats[RAVB_BE].rx_over_errors;
	priv->rx_over_errors += priv->stats[RAVB_NC].rx_over_errors;
	if (priv->rx_over_errors != ndev->stats.rx_over_errors)
		ndev->stats.rx_over_errors = priv->rx_over_errors;
	if (priv->rx_fifo_errors != ndev->stats.rx_fifo_errors)
		ndev->stats.rx_fifo_errors = priv->rx_fifo_errors;
out:
	return budget - quota;
}