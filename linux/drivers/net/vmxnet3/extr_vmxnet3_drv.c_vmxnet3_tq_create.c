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
struct TYPE_7__ {int size; void* base; int /*<<< orphan*/  basePA; } ;
struct TYPE_6__ {int size; void* base; int /*<<< orphan*/  basePA; } ;
struct TYPE_5__ {size_t size; void* base; int /*<<< orphan*/  basePA; } ;
struct vmxnet3_tx_queue {size_t txdata_desc_size; void* buf_info; int /*<<< orphan*/  buf_info_pa; TYPE_3__ tx_ring; TYPE_2__ comp_ring; TYPE_1__ data_ring; } ;
struct vmxnet3_adapter {TYPE_4__* pdev; int /*<<< orphan*/  netdev; } ;
struct Vmxnet3_TxDesc {int dummy; } ;
struct Vmxnet3_TxCompDesc {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vmxnet3_tq_destroy (struct vmxnet3_tx_queue*,struct vmxnet3_adapter*) ; 

__attribute__((used)) static int
vmxnet3_tq_create(struct vmxnet3_tx_queue *tq,
		  struct vmxnet3_adapter *adapter)
{
	size_t sz;

	BUG_ON(tq->tx_ring.base || tq->data_ring.base ||
	       tq->comp_ring.base || tq->buf_info);

	tq->tx_ring.base = dma_alloc_coherent(&adapter->pdev->dev,
			tq->tx_ring.size * sizeof(struct Vmxnet3_TxDesc),
			&tq->tx_ring.basePA, GFP_KERNEL);
	if (!tq->tx_ring.base) {
		netdev_err(adapter->netdev, "failed to allocate tx ring\n");
		goto err;
	}

	tq->data_ring.base = dma_alloc_coherent(&adapter->pdev->dev,
			tq->data_ring.size * tq->txdata_desc_size,
			&tq->data_ring.basePA, GFP_KERNEL);
	if (!tq->data_ring.base) {
		netdev_err(adapter->netdev, "failed to allocate tx data ring\n");
		goto err;
	}

	tq->comp_ring.base = dma_alloc_coherent(&adapter->pdev->dev,
			tq->comp_ring.size * sizeof(struct Vmxnet3_TxCompDesc),
			&tq->comp_ring.basePA, GFP_KERNEL);
	if (!tq->comp_ring.base) {
		netdev_err(adapter->netdev, "failed to allocate tx comp ring\n");
		goto err;
	}

	sz = tq->tx_ring.size * sizeof(tq->buf_info[0]);
	tq->buf_info = dma_alloc_coherent(&adapter->pdev->dev, sz,
					  &tq->buf_info_pa, GFP_KERNEL);
	if (!tq->buf_info)
		goto err;

	return 0;

err:
	vmxnet3_tq_destroy(tq, adapter);
	return -ENOMEM;
}