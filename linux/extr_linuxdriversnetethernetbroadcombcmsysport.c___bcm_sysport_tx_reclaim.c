#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct net_device {int dummy; } ;
struct bcm_sysport_tx_ring {unsigned int c_index; size_t clean_index; int size; unsigned int packets; unsigned int bytes; scalar_t__ index; int /*<<< orphan*/  desc_count; struct bcm_sysport_cb* cbs; TYPE_1__* priv; } ;
struct bcm_sysport_priv {int /*<<< orphan*/  syncp; struct net_device* netdev; } ;
struct bcm_sysport_cb {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  is_lite; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 scalar_t__ INTRL2_0_TDMA_MBDONE_SHIFT ; 
 int /*<<< orphan*/  INTRL2_CPU_CLEAR ; 
 unsigned int RING_CONS_INDEX_MASK ; 
 unsigned int RING_CONS_INDEX_SHIFT ; 
 int /*<<< orphan*/  TDMA_DESC_RING_PROD_CONS_INDEX (scalar_t__) ; 
 int /*<<< orphan*/  bcm_sysport_tx_reclaim_one (struct bcm_sysport_tx_ring*,struct bcm_sysport_cb*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  intrl2_0_writel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intrl2_1_writel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netif_dbg (struct bcm_sysport_priv*,int /*<<< orphan*/ ,struct net_device*,char*,scalar_t__,unsigned int,unsigned int,unsigned int) ; 
 unsigned int tdma_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_done ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int __bcm_sysport_tx_reclaim(struct bcm_sysport_priv *priv,
					     struct bcm_sysport_tx_ring *ring)
{
	unsigned int pkts_compl = 0, bytes_compl = 0;
	struct net_device *ndev = priv->netdev;
	unsigned int txbds_processed = 0;
	struct bcm_sysport_cb *cb;
	unsigned int txbds_ready;
	unsigned int c_index;
	u32 hw_ind;

	/* Clear status before servicing to reduce spurious interrupts */
	if (!ring->priv->is_lite)
		intrl2_1_writel(ring->priv, BIT(ring->index), INTRL2_CPU_CLEAR);
	else
		intrl2_0_writel(ring->priv, BIT(ring->index +
				INTRL2_0_TDMA_MBDONE_SHIFT), INTRL2_CPU_CLEAR);

	/* Compute how many descriptors have been processed since last call */
	hw_ind = tdma_readl(priv, TDMA_DESC_RING_PROD_CONS_INDEX(ring->index));
	c_index = (hw_ind >> RING_CONS_INDEX_SHIFT) & RING_CONS_INDEX_MASK;
	txbds_ready = (c_index - ring->c_index) & RING_CONS_INDEX_MASK;

	netif_dbg(priv, tx_done, ndev,
		  "ring=%d old_c_index=%u c_index=%u txbds_ready=%u\n",
		  ring->index, ring->c_index, c_index, txbds_ready);

	while (txbds_processed < txbds_ready) {
		cb = &ring->cbs[ring->clean_index];
		bcm_sysport_tx_reclaim_one(ring, cb, &bytes_compl, &pkts_compl);

		ring->desc_count++;
		txbds_processed++;

		if (likely(ring->clean_index < ring->size - 1))
			ring->clean_index++;
		else
			ring->clean_index = 0;
	}

	u64_stats_update_begin(&priv->syncp);
	ring->packets += pkts_compl;
	ring->bytes += bytes_compl;
	u64_stats_update_end(&priv->syncp);

	ring->c_index = c_index;

	netif_dbg(priv, tx_done, ndev,
		  "ring=%d c_index=%d pkts_compl=%d, bytes_compl=%d\n",
		  ring->index, ring->c_index, pkts_compl, bytes_compl);

	return pkts_compl;
}