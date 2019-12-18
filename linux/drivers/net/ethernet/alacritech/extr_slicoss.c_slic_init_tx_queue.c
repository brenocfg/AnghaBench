#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct slic_tx_queue {unsigned int len; struct slic_tx_buffer* txbuffs; int /*<<< orphan*/  dma_pool; scalar_t__ done_idx; scalar_t__ put_idx; } ;
struct slic_tx_desc {void* type; scalar_t__ flags; int /*<<< orphan*/  cmd; void* hnd; } ;
struct slic_tx_buffer {int /*<<< orphan*/  desc_paddr; struct slic_tx_desc* desc; } ;
struct slic_device {int /*<<< orphan*/  netdev; TYPE_1__* pdev; struct slic_tx_queue txq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SLIC_CMD_TYPE_DUMB ; 
 int /*<<< orphan*/  SLIC_CMD_XMT_REQ ; 
 unsigned int SLIC_NUM_TX_DESCS ; 
 int /*<<< orphan*/  SLIC_TX_DESC_ALIGN ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_create (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct slic_tx_desc*,int /*<<< orphan*/ ) ; 
 struct slic_tx_desc* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct slic_tx_buffer* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct slic_tx_buffer*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int slic_init_tx_queue(struct slic_device *sdev)
{
	struct slic_tx_queue *txq = &sdev->txq;
	struct slic_tx_buffer *buff;
	struct slic_tx_desc *desc;
	unsigned int i;
	int err;

	txq->len = SLIC_NUM_TX_DESCS;
	txq->put_idx = 0;
	txq->done_idx = 0;

	txq->txbuffs = kcalloc(txq->len, sizeof(*buff), GFP_KERNEL);
	if (!txq->txbuffs)
		return -ENOMEM;

	txq->dma_pool = dma_pool_create("slic_pool", &sdev->pdev->dev,
					sizeof(*desc), SLIC_TX_DESC_ALIGN,
					4096);
	if (!txq->dma_pool) {
		err = -ENOMEM;
		netdev_err(sdev->netdev, "failed to create dma pool\n");
		goto free_buffs;
	}

	for (i = 0; i < txq->len; i++) {
		buff = &txq->txbuffs[i];
		desc = dma_pool_zalloc(txq->dma_pool, GFP_KERNEL,
				       &buff->desc_paddr);
		if (!desc) {
			netdev_err(sdev->netdev,
				   "failed to alloc pool chunk (%i)\n", i);
			err = -ENOMEM;
			goto free_descs;
		}

		desc->hnd = cpu_to_le32((u32)(i + 1));
		desc->cmd = SLIC_CMD_XMT_REQ;
		desc->flags = 0;
		desc->type = cpu_to_le32(SLIC_CMD_TYPE_DUMB);
		buff->desc = desc;
	}

	return 0;

free_descs:
	while (i--) {
		buff = &txq->txbuffs[i];
		dma_pool_free(txq->dma_pool, buff->desc, buff->desc_paddr);
	}
	dma_pool_destroy(txq->dma_pool);

free_buffs:
	kfree(txq->txbuffs);

	return err;
}