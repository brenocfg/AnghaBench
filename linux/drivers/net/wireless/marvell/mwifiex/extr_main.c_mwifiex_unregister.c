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
struct TYPE_2__ {int /*<<< orphan*/  (* cleanup_if ) (struct mwifiex_adapter*) ;} ;
struct mwifiex_adapter {size_t priv_num; size_t n_matches; struct mwifiex_adapter* regd; struct mwifiex_adapter* nd_info; struct mwifiex_adapter** matches; struct mwifiex_adapter** priv; int /*<<< orphan*/  cmd_timer; TYPE_1__ if_ops; } ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_free_curr_bcn (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  stub1 (struct mwifiex_adapter*) ; 

__attribute__((used)) static int mwifiex_unregister(struct mwifiex_adapter *adapter)
{
	s32 i;

	if (adapter->if_ops.cleanup_if)
		adapter->if_ops.cleanup_if(adapter);

	del_timer_sync(&adapter->cmd_timer);

	/* Free private structures */
	for (i = 0; i < adapter->priv_num; i++) {
		if (adapter->priv[i]) {
			mwifiex_free_curr_bcn(adapter->priv[i]);
			kfree(adapter->priv[i]);
		}
	}

	if (adapter->nd_info) {
		for (i = 0 ; i < adapter->nd_info->n_matches ; i++)
			kfree(adapter->nd_info->matches[i]);
		kfree(adapter->nd_info);
		adapter->nd_info = NULL;
	}

	kfree(adapter->regd);

	kfree(adapter);
	return 0;
}