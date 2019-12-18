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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct hinic_sge {int dummy; } ;
struct hinic_rxq {int /*<<< orphan*/  rq; int /*<<< orphan*/  netdev; } ;
struct hinic_rq_wqe {int dummy; } ;
struct hinic_dev {unsigned int rx_weight; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_RQ_WQE_SIZE ; 
 unsigned int hinic_get_rq_free_wqebbs (int /*<<< orphan*/ ) ; 
 struct hinic_rq_wqe* hinic_rq_get_wqe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hinic_rq_prepare_wqe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hinic_rq_wqe*,struct hinic_sge*) ; 
 int /*<<< orphan*/  hinic_rq_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_rq_write_wqe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hinic_rq_wqe*,struct sk_buff*) ; 
 int /*<<< orphan*/  hinic_set_sge (struct hinic_sge*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct hinic_dev* netdev_priv (int /*<<< orphan*/ ) ; 
 struct sk_buff* rx_alloc_skb (struct hinic_rxq*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_free_skb (struct hinic_rxq*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int rx_alloc_pkts(struct hinic_rxq *rxq)
{
	struct hinic_dev *nic_dev = netdev_priv(rxq->netdev);
	struct hinic_rq_wqe *rq_wqe;
	unsigned int free_wqebbs;
	struct hinic_sge sge;
	dma_addr_t dma_addr;
	struct sk_buff *skb;
	u16 prod_idx;
	int i;

	free_wqebbs = hinic_get_rq_free_wqebbs(rxq->rq);

	/* Limit the allocation chunks */
	if (free_wqebbs > nic_dev->rx_weight)
		free_wqebbs = nic_dev->rx_weight;

	for (i = 0; i < free_wqebbs; i++) {
		skb = rx_alloc_skb(rxq, &dma_addr);
		if (!skb) {
			netdev_err(rxq->netdev, "Failed to alloc Rx skb\n");
			goto skb_out;
		}

		hinic_set_sge(&sge, dma_addr, skb->len);

		rq_wqe = hinic_rq_get_wqe(rxq->rq, HINIC_RQ_WQE_SIZE,
					  &prod_idx);
		if (!rq_wqe) {
			rx_free_skb(rxq, skb, dma_addr);
			goto skb_out;
		}

		hinic_rq_prepare_wqe(rxq->rq, prod_idx, rq_wqe, &sge);

		hinic_rq_write_wqe(rxq->rq, prod_idx, rq_wqe, skb);
	}

skb_out:
	if (i) {
		wmb();  /* write all the wqes before update PI */

		hinic_rq_update(rxq->rq, prod_idx);
	}

	return i;
}