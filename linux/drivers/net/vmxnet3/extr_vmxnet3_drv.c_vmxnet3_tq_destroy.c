#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; int /*<<< orphan*/ * base; int /*<<< orphan*/  basePA; } ;
struct TYPE_6__ {int size; int /*<<< orphan*/ * base; int /*<<< orphan*/  basePA; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/ * base; int /*<<< orphan*/  basePA; } ;
struct vmxnet3_tx_queue {int txdata_desc_size; int /*<<< orphan*/ * buf_info; int /*<<< orphan*/  buf_info_pa; TYPE_4__ tx_ring; TYPE_2__ comp_ring; TYPE_1__ data_ring; } ;
struct vmxnet3_adapter {TYPE_3__* pdev; } ;
struct Vmxnet3_TxDesc {int dummy; } ;
struct Vmxnet3_TxCompDesc {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmxnet3_tq_destroy(struct vmxnet3_tx_queue *tq,
		   struct vmxnet3_adapter *adapter)
{
	if (tq->tx_ring.base) {
		dma_free_coherent(&adapter->pdev->dev, tq->tx_ring.size *
				  sizeof(struct Vmxnet3_TxDesc),
				  tq->tx_ring.base, tq->tx_ring.basePA);
		tq->tx_ring.base = NULL;
	}
	if (tq->data_ring.base) {
		dma_free_coherent(&adapter->pdev->dev,
				  tq->data_ring.size * tq->txdata_desc_size,
				  tq->data_ring.base, tq->data_ring.basePA);
		tq->data_ring.base = NULL;
	}
	if (tq->comp_ring.base) {
		dma_free_coherent(&adapter->pdev->dev, tq->comp_ring.size *
				  sizeof(struct Vmxnet3_TxCompDesc),
				  tq->comp_ring.base, tq->comp_ring.basePA);
		tq->comp_ring.base = NULL;
	}
	if (tq->buf_info) {
		dma_free_coherent(&adapter->pdev->dev,
				  tq->tx_ring.size * sizeof(tq->buf_info[0]),
				  tq->buf_info, tq->buf_info_pa);
		tq->buf_info = NULL;
	}
}