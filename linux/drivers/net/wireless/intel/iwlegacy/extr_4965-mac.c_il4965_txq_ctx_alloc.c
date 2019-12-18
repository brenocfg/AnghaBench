#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dma; } ;
struct TYPE_4__ {int max_txq_num; int /*<<< orphan*/  scd_bc_tbls_size; } ;
struct il_priv {TYPE_2__ scd_bc_tbls; TYPE_2__ kw; TYPE_1__ hw_params; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FH49_KW_MEM_ADDR_REG ; 
 int /*<<< orphan*/  IL_ERR (char*,...) ; 
 int /*<<< orphan*/  IL_KW_SIZE ; 
 int il4965_alloc_dma_ptr (struct il_priv*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_free_dma_ptr (struct il_priv*,TYPE_2__*) ; 
 int /*<<< orphan*/  il4965_hw_txq_ctx_free (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_txq_set_sched (struct il_priv*,int /*<<< orphan*/ ) ; 
 int il_alloc_txq_mem (struct il_priv*) ; 
 int il_tx_queue_init (struct il_priv*,int) ; 
 int /*<<< orphan*/  il_wr (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
il4965_txq_ctx_alloc(struct il_priv *il)
{
	int ret, txq_id;
	unsigned long flags;

	/* Free all tx/cmd queues and keep-warm buffer */
	il4965_hw_txq_ctx_free(il);

	ret =
	    il4965_alloc_dma_ptr(il, &il->scd_bc_tbls,
				 il->hw_params.scd_bc_tbls_size);
	if (ret) {
		IL_ERR("Scheduler BC Table allocation failed\n");
		goto error_bc_tbls;
	}
	/* Alloc keep-warm buffer */
	ret = il4965_alloc_dma_ptr(il, &il->kw, IL_KW_SIZE);
	if (ret) {
		IL_ERR("Keep Warm allocation failed\n");
		goto error_kw;
	}

	/* allocate tx queue structure */
	ret = il_alloc_txq_mem(il);
	if (ret)
		goto error;

	spin_lock_irqsave(&il->lock, flags);

	/* Turn off all Tx DMA fifos */
	il4965_txq_set_sched(il, 0);

	/* Tell NIC where to find the "keep warm" buffer */
	il_wr(il, FH49_KW_MEM_ADDR_REG, il->kw.dma >> 4);

	spin_unlock_irqrestore(&il->lock, flags);

	/* Alloc and init all Tx queues, including the command queue (#4/#9) */
	for (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++) {
		ret = il_tx_queue_init(il, txq_id);
		if (ret) {
			IL_ERR("Tx %d queue init failed\n", txq_id);
			goto error;
		}
	}

	return ret;

error:
	il4965_hw_txq_ctx_free(il);
	il4965_free_dma_ptr(il, &il->kw);
error_kw:
	il4965_free_dma_ptr(il, &il->scd_bc_tbls);
error_bc_tbls:
	return ret;
}