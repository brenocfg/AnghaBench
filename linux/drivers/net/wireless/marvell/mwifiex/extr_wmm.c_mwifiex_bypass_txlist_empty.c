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
struct mwifiex_private {int /*<<< orphan*/  bypass_txq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* is_port_ready ) (struct mwifiex_private*) ;} ;
struct mwifiex_adapter {int priv_num; TYPE_1__ if_ops; struct mwifiex_private** priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mwifiex_private*) ; 

int mwifiex_bypass_txlist_empty(struct mwifiex_adapter *adapter)
{
	struct mwifiex_private *priv;
	int i;

	for (i = 0; i < adapter->priv_num; i++) {
		priv = adapter->priv[i];
		if (!priv)
			continue;
		if (adapter->if_ops.is_port_ready &&
		    !adapter->if_ops.is_port_ready(priv))
			continue;
		if (!skb_queue_empty(&priv->bypass_txq))
			return false;
	}

	return true;
}