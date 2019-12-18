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
struct netsec_priv {int /*<<< orphan*/  ndev; struct netsec_desc_ring* desc_ring; } ;
struct netsec_desc_ring {int dummy; } ;

/* Variables and functions */
 int DESC_NUM ; 
 int NETDEV_TX_BUSY ; 
 size_t NETSEC_RING_TX ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int netsec_desc_used (struct netsec_desc_ring*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static int netsec_check_stop_tx(struct netsec_priv *priv, int used)
{
	struct netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_TX];

	/* keep tail from touching the queue */
	if (DESC_NUM - used < 2) {
		netif_stop_queue(priv->ndev);

		/* Make sure we read the updated value in case
		 * descriptors got freed
		 */
		smp_rmb();

		used = netsec_desc_used(dring);
		if (DESC_NUM - used < 2)
			return NETDEV_TX_BUSY;

		netif_wake_queue(priv->ndev);
	}

	return 0;
}