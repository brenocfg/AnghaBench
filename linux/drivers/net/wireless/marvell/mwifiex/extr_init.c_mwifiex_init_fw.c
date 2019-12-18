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
typedef  size_t u8 ;
struct mwifiex_private {int dummy; } ;
struct mwifiex_adapter {size_t priv_num; void* hw_status; int /*<<< orphan*/  cmd_pending_q_lock; int /*<<< orphan*/  cmd_pending_q; struct mwifiex_private** priv; scalar_t__ mfg_mode; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 void* MWIFIEX_HW_STATUS_INITIALIZING ; 
 void* MWIFIEX_HW_STATUS_READY ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int mwifiex_allocate_adapter (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_init_adapter (struct mwifiex_adapter*) ; 
 int mwifiex_init_priv (struct mwifiex_private*) ; 
 int mwifiex_main_process (struct mwifiex_adapter*) ; 
 int mwifiex_sta_init_cmd (struct mwifiex_private*,size_t,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int mwifiex_init_fw(struct mwifiex_adapter *adapter)
{
	int ret;
	struct mwifiex_private *priv;
	u8 i, first_sta = true;
	int is_cmd_pend_q_empty;

	adapter->hw_status = MWIFIEX_HW_STATUS_INITIALIZING;

	/* Allocate memory for member of adapter structure */
	ret = mwifiex_allocate_adapter(adapter);
	if (ret)
		return -1;

	/* Initialize adapter structure */
	mwifiex_init_adapter(adapter);

	for (i = 0; i < adapter->priv_num; i++) {
		if (adapter->priv[i]) {
			priv = adapter->priv[i];

			/* Initialize private structure */
			ret = mwifiex_init_priv(priv);
			if (ret)
				return -1;
		}
	}
	if (adapter->mfg_mode) {
		adapter->hw_status = MWIFIEX_HW_STATUS_READY;
		ret = -EINPROGRESS;
	} else {
		for (i = 0; i < adapter->priv_num; i++) {
			if (adapter->priv[i]) {
				ret = mwifiex_sta_init_cmd(adapter->priv[i],
							   first_sta, true);
				if (ret == -1)
					return -1;

				first_sta = false;
			}



		}
	}

	spin_lock_bh(&adapter->cmd_pending_q_lock);
	is_cmd_pend_q_empty = list_empty(&adapter->cmd_pending_q);
	spin_unlock_bh(&adapter->cmd_pending_q_lock);
	if (!is_cmd_pend_q_empty) {
		/* Send the first command in queue and return */
		if (mwifiex_main_process(adapter) != -1)
			ret = -EINPROGRESS;
	} else {
		adapter->hw_status = MWIFIEX_HW_STATUS_READY;
	}

	return ret;
}