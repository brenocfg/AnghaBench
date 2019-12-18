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
struct lan743x_tx {int /*<<< orphan*/ * overflow_skb; int /*<<< orphan*/  channel_number; int /*<<< orphan*/  napi; struct lan743x_adapter* adapter; } ;
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAC_CMD ; 
 int /*<<< orphan*/  DMAC_CMD_STOP_T_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMAC_INT_BIT_TX_IOC_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMAC_INT_EN_CLR ; 
 int /*<<< orphan*/  FCT_TX_CTL ; 
 int /*<<< orphan*/  FCT_TX_CTL_DIS_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCT_TX_CTL_EN_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_BIT_DMA_TX_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_EN_CLR ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lan743x_csr_wait_for_bit (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_dmac_tx_wait_till_stopped (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_tx_release_all_descriptors (struct lan743x_tx*) ; 
 int /*<<< orphan*/  lan743x_tx_ring_cleanup (struct lan743x_tx*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lan743x_tx_close(struct lan743x_tx *tx)
{
	struct lan743x_adapter *adapter = tx->adapter;

	lan743x_csr_write(adapter,
			  DMAC_CMD,
			  DMAC_CMD_STOP_T_(tx->channel_number));
	lan743x_dmac_tx_wait_till_stopped(adapter, tx->channel_number);

	lan743x_csr_write(adapter,
			  DMAC_INT_EN_CLR,
			  DMAC_INT_BIT_TX_IOC_(tx->channel_number));
	lan743x_csr_write(adapter, INT_EN_CLR,
			  INT_BIT_DMA_TX_(tx->channel_number));
	napi_disable(&tx->napi);
	netif_napi_del(&tx->napi);

	lan743x_csr_write(adapter, FCT_TX_CTL,
			  FCT_TX_CTL_DIS_(tx->channel_number));
	lan743x_csr_wait_for_bit(adapter, FCT_TX_CTL,
				 FCT_TX_CTL_EN_(tx->channel_number),
				 0, 1000, 20000, 100);

	lan743x_tx_release_all_descriptors(tx);

	if (tx->overflow_skb) {
		dev_kfree_skb(tx->overflow_skb);
		tx->overflow_skb = NULL;
	}

	lan743x_tx_ring_cleanup(tx);
}