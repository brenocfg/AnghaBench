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
typedef  size_t u16 ;
struct hinic_sge {int dummy; } ;
struct hinic_rxq {struct hinic_rq* rq; } ;
struct hinic_rq {int /*<<< orphan*/ * saved_skb; int /*<<< orphan*/  wq; } ;
struct hinic_hw_wqe {int /*<<< orphan*/  rq_wqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_RQ_WQE_SIZE ; 
 scalar_t__ IS_ERR (struct hinic_hw_wqe*) ; 
 int /*<<< orphan*/  hinic_put_wqe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hinic_hw_wqe* hinic_read_wqe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  hinic_rq_get_sge (struct hinic_rq*,int /*<<< orphan*/ *,size_t,struct hinic_sge*) ; 
 int /*<<< orphan*/  hinic_sge_to_dma (struct hinic_sge*) ; 
 int /*<<< orphan*/  rx_free_skb (struct hinic_rxq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_all_rx_skbs(struct hinic_rxq *rxq)
{
	struct hinic_rq *rq = rxq->rq;
	struct hinic_hw_wqe *hw_wqe;
	struct hinic_sge sge;
	u16 ci;

	while ((hw_wqe = hinic_read_wqe(rq->wq, HINIC_RQ_WQE_SIZE, &ci))) {
		if (IS_ERR(hw_wqe))
			break;

		hinic_rq_get_sge(rq, &hw_wqe->rq_wqe, ci, &sge);

		hinic_put_wqe(rq->wq, HINIC_RQ_WQE_SIZE);

		rx_free_skb(rxq, rq->saved_skb[ci], hinic_sge_to_dma(&sge));
	}
}