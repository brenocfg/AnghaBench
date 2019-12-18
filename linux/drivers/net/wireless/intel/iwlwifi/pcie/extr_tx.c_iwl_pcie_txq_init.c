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
typedef  int u32 ;
struct lock_class_key {int dummy; } ;
struct iwl_txq {int need_update; int /*<<< orphan*/  overflow_q; int /*<<< orphan*/  lock; } ;
struct iwl_trans {TYPE_2__* trans_cfg; } ;
struct TYPE_4__ {TYPE_1__* base_params; } ;
struct TYPE_3__ {int max_tfd_queue_size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int iwl_queue_init (struct iwl_txq*,int) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,struct lock_class_key*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int iwl_pcie_txq_init(struct iwl_trans *trans, struct iwl_txq *txq,
		      int slots_num, bool cmd_queue)
{
	int ret;
	u32 tfd_queue_max_size =
		trans->trans_cfg->base_params->max_tfd_queue_size;

	txq->need_update = false;

	/* max_tfd_queue_size must be power-of-two size, otherwise
	 * iwl_queue_inc_wrap and iwl_queue_dec_wrap are broken. */
	if (WARN_ONCE(tfd_queue_max_size & (tfd_queue_max_size - 1),
		      "Max tfd queue size must be a power of two, but is %d",
		      tfd_queue_max_size))
		return -EINVAL;

	/* Initialize queue's high/low-water marks, and head/tail indexes */
	ret = iwl_queue_init(txq, slots_num);
	if (ret)
		return ret;

	spin_lock_init(&txq->lock);

	if (cmd_queue) {
		static struct lock_class_key iwl_pcie_cmd_queue_lock_class;

		lockdep_set_class(&txq->lock, &iwl_pcie_cmd_queue_lock_class);
	}

	__skb_queue_head_init(&txq->overflow_q);

	return 0;
}