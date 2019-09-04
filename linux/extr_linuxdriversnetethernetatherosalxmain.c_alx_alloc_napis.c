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
struct alx_tx_queue {int queue_idx; int /*<<< orphan*/ * dev; int /*<<< orphan*/  netdev; int /*<<< orphan*/  count; int /*<<< orphan*/  c_reg; int /*<<< orphan*/  p_reg; } ;
struct alx_rx_queue {int /*<<< orphan*/ * dev; int /*<<< orphan*/  netdev; int /*<<< orphan*/  count; scalar_t__ queue_idx; struct alx_napi* np; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct alx_priv {int num_napi; int num_txq; int /*<<< orphan*/  dev; int /*<<< orphan*/  int_mask; TYPE_2__ hw; int /*<<< orphan*/  rx_ringsz; struct alx_napi** qnapi; int /*<<< orphan*/  tx_ringsz; } ;
struct alx_napi {int /*<<< orphan*/  vec_mask; struct alx_rx_queue* rxq; struct alx_tx_queue* txq; int /*<<< orphan*/  napi; struct alx_priv* alx; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_ISR_ALL_QUEUES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alx_free_napis (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_poll ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * rx_vect_mask ; 
 int /*<<< orphan*/ * tx_cidx_reg ; 
 int /*<<< orphan*/ * tx_pidx_reg ; 
 int /*<<< orphan*/ * tx_vect_mask ; 

__attribute__((used)) static int alx_alloc_napis(struct alx_priv *alx)
{
	struct alx_napi *np;
	struct alx_rx_queue *rxq;
	struct alx_tx_queue *txq;
	int i;

	alx->int_mask &= ~ALX_ISR_ALL_QUEUES;

	/* allocate alx_napi structures */
	for (i = 0; i < alx->num_napi; i++) {
		np = kzalloc(sizeof(struct alx_napi), GFP_KERNEL);
		if (!np)
			goto err_out;

		np->alx = alx;
		netif_napi_add(alx->dev, &np->napi, alx_poll, 64);
		alx->qnapi[i] = np;
	}

	/* allocate tx queues */
	for (i = 0; i < alx->num_txq; i++) {
		np = alx->qnapi[i];
		txq = kzalloc(sizeof(*txq), GFP_KERNEL);
		if (!txq)
			goto err_out;

		np->txq = txq;
		txq->p_reg = tx_pidx_reg[i];
		txq->c_reg = tx_cidx_reg[i];
		txq->queue_idx = i;
		txq->count = alx->tx_ringsz;
		txq->netdev = alx->dev;
		txq->dev = &alx->hw.pdev->dev;
		np->vec_mask |= tx_vect_mask[i];
		alx->int_mask |= tx_vect_mask[i];
	}

	/* allocate rx queues */
	np = alx->qnapi[0];
	rxq = kzalloc(sizeof(*rxq), GFP_KERNEL);
	if (!rxq)
		goto err_out;

	np->rxq = rxq;
	rxq->np = alx->qnapi[0];
	rxq->queue_idx = 0;
	rxq->count = alx->rx_ringsz;
	rxq->netdev = alx->dev;
	rxq->dev = &alx->hw.pdev->dev;
	np->vec_mask |= rx_vect_mask[0];
	alx->int_mask |= rx_vect_mask[0];

	return 0;

err_out:
	netdev_err(alx->dev, "error allocating internal structures\n");
	alx_free_napis(alx);
	return -ENOMEM;
}