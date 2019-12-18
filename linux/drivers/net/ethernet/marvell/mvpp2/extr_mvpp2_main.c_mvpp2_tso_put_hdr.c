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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct mvpp2_txq_pcpu {int txq_put_index; scalar_t__ tso_headers_dma; } ;
struct mvpp2_tx_queue {int /*<<< orphan*/  id; } ;
struct mvpp2_tx_desc {int dummy; } ;
struct mvpp2_port {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int MVPP2_TXD_F_DESC ; 
 int MVPP2_TXD_PADDING_DISABLE ; 
 int TSO_HEADER_SIZE ; 
 int mvpp2_skb_tx_csum (struct mvpp2_port*,struct sk_buff*) ; 
 int /*<<< orphan*/  mvpp2_txdesc_cmd_set (struct mvpp2_port*,struct mvpp2_tx_desc*,int) ; 
 int /*<<< orphan*/  mvpp2_txdesc_dma_addr_set (struct mvpp2_port*,struct mvpp2_tx_desc*,scalar_t__) ; 
 int /*<<< orphan*/  mvpp2_txdesc_size_set (struct mvpp2_port*,struct mvpp2_tx_desc*,int) ; 
 int /*<<< orphan*/  mvpp2_txdesc_txq_set (struct mvpp2_port*,struct mvpp2_tx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_txq_inc_put (struct mvpp2_port*,struct mvpp2_txq_pcpu*,int /*<<< orphan*/ *,struct mvpp2_tx_desc*) ; 
 struct mvpp2_tx_desc* mvpp2_txq_next_desc_get (struct mvpp2_tx_queue*) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline void mvpp2_tso_put_hdr(struct sk_buff *skb,
				     struct net_device *dev,
				     struct mvpp2_tx_queue *txq,
				     struct mvpp2_tx_queue *aggr_txq,
				     struct mvpp2_txq_pcpu *txq_pcpu,
				     int hdr_sz)
{
	struct mvpp2_port *port = netdev_priv(dev);
	struct mvpp2_tx_desc *tx_desc = mvpp2_txq_next_desc_get(aggr_txq);
	dma_addr_t addr;

	mvpp2_txdesc_txq_set(port, tx_desc, txq->id);
	mvpp2_txdesc_size_set(port, tx_desc, hdr_sz);

	addr = txq_pcpu->tso_headers_dma +
	       txq_pcpu->txq_put_index * TSO_HEADER_SIZE;
	mvpp2_txdesc_dma_addr_set(port, tx_desc, addr);

	mvpp2_txdesc_cmd_set(port, tx_desc, mvpp2_skb_tx_csum(port, skb) |
					    MVPP2_TXD_F_DESC |
					    MVPP2_TXD_PADDING_DISABLE);
	mvpp2_txq_inc_put(port, txq_pcpu, NULL, tx_desc);
}