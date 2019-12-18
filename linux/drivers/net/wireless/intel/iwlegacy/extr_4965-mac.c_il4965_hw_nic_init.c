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
struct il_rx_queue {int need_update; int /*<<< orphan*/  bd; } ;
struct il_priv {int /*<<< orphan*/  status; int /*<<< orphan*/  txq; int /*<<< orphan*/  lock; struct il_rx_queue rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_INT_COALESCING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int /*<<< orphan*/  IL_HOST_INT_CALIB_TIMEOUT_DEF ; 
 int /*<<< orphan*/  S_INIT ; 
 int /*<<< orphan*/  il4965_nic_config (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_rx_init (struct il_priv*,struct il_rx_queue*) ; 
 int /*<<< orphan*/  il4965_rx_queue_reset (struct il_priv*,struct il_rx_queue*) ; 
 int /*<<< orphan*/  il4965_rx_replenish (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_set_pwr_vmain (struct il_priv*) ; 
 int il4965_txq_ctx_alloc (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_txq_ctx_reset (struct il_priv*) ; 
 int /*<<< orphan*/  il_apm_init (struct il_priv*) ; 
 int il_rx_queue_alloc (struct il_priv*) ; 
 int /*<<< orphan*/  il_rx_queue_update_write_ptr (struct il_priv*,struct il_rx_queue*) ; 
 int /*<<< orphan*/  il_write8 (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
il4965_hw_nic_init(struct il_priv *il)
{
	unsigned long flags;
	struct il_rx_queue *rxq = &il->rxq;
	int ret;

	spin_lock_irqsave(&il->lock, flags);
	il_apm_init(il);
	/* Set interrupt coalescing calibration timer to default (512 usecs) */
	il_write8(il, CSR_INT_COALESCING, IL_HOST_INT_CALIB_TIMEOUT_DEF);
	spin_unlock_irqrestore(&il->lock, flags);

	il4965_set_pwr_vmain(il);
	il4965_nic_config(il);

	/* Allocate the RX queue, or reset if it is already allocated */
	if (!rxq->bd) {
		ret = il_rx_queue_alloc(il);
		if (ret) {
			IL_ERR("Unable to initialize Rx queue\n");
			return -ENOMEM;
		}
	} else
		il4965_rx_queue_reset(il, rxq);

	il4965_rx_replenish(il);

	il4965_rx_init(il, rxq);

	spin_lock_irqsave(&il->lock, flags);

	rxq->need_update = 1;
	il_rx_queue_update_write_ptr(il, rxq);

	spin_unlock_irqrestore(&il->lock, flags);

	/* Allocate or reset and init all Tx and Command queues */
	if (!il->txq) {
		ret = il4965_txq_ctx_alloc(il);
		if (ret)
			return ret;
	} else
		il4965_txq_ctx_reset(il);

	set_bit(S_INIT, &il->status);

	return 0;
}