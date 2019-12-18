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
struct iwl_mvm_reorder_buffer {int buf_size; int removed; int /*<<< orphan*/  reorder_timer; int /*<<< orphan*/  lock; int /*<<< orphan*/  num_stored; } ;
struct TYPE_4__ {int /*<<< orphan*/  frames; } ;
struct iwl_mvm_reorder_buf_entry {TYPE_2__ e; } ;
struct iwl_mvm_baid_data {int entries_per_queue; struct iwl_mvm_reorder_buf_entry* entries; struct iwl_mvm_reorder_buffer* reorder_buf; int /*<<< orphan*/  baid; } ;
struct iwl_mvm {TYPE_1__* trans; } ;
struct TYPE_3__ {int num_rx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_sync_rxq_del_ba (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_free_reorder(struct iwl_mvm *mvm,
				 struct iwl_mvm_baid_data *data)
{
	int i;

	iwl_mvm_sync_rxq_del_ba(mvm, data->baid);

	for (i = 0; i < mvm->trans->num_rx_queues; i++) {
		int j;
		struct iwl_mvm_reorder_buffer *reorder_buf =
			&data->reorder_buf[i];
		struct iwl_mvm_reorder_buf_entry *entries =
			&data->entries[i * data->entries_per_queue];

		spin_lock_bh(&reorder_buf->lock);
		if (likely(!reorder_buf->num_stored)) {
			spin_unlock_bh(&reorder_buf->lock);
			continue;
		}

		/*
		 * This shouldn't happen in regular DELBA since the internal
		 * delBA notification should trigger a release of all frames in
		 * the reorder buffer.
		 */
		WARN_ON(1);

		for (j = 0; j < reorder_buf->buf_size; j++)
			__skb_queue_purge(&entries[j].e.frames);
		/*
		 * Prevent timer re-arm. This prevents a very far fetched case
		 * where we timed out on the notification. There may be prior
		 * RX frames pending in the RX queue before the notification
		 * that might get processed between now and the actual deletion
		 * and we would re-arm the timer although we are deleting the
		 * reorder buffer.
		 */
		reorder_buf->removed = true;
		spin_unlock_bh(&reorder_buf->lock);
		del_timer_sync(&reorder_buf->reorder_timer);
	}
}