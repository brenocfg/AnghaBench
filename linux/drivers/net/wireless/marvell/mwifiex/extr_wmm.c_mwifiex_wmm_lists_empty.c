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
struct TYPE_3__ {int /*<<< orphan*/  tx_pkts_queued; } ;
struct mwifiex_private {scalar_t__ bss_mode; TYPE_1__ wmm; int /*<<< orphan*/  port_open; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* is_port_ready ) (struct mwifiex_private*) ;} ;
struct mwifiex_adapter {int priv_num; TYPE_2__ if_ops; struct mwifiex_private** priv; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mwifiex_private*) ; 

int
mwifiex_wmm_lists_empty(struct mwifiex_adapter *adapter)
{
	int i;
	struct mwifiex_private *priv;

	for (i = 0; i < adapter->priv_num; ++i) {
		priv = adapter->priv[i];
		if (!priv)
			continue;
		if (!priv->port_open &&
		    (priv->bss_mode != NL80211_IFTYPE_ADHOC))
			continue;
		if (adapter->if_ops.is_port_ready &&
		    !adapter->if_ops.is_port_ready(priv))
			continue;
		if (atomic_read(&priv->wmm.tx_pkts_queued))
			return false;
	}

	return true;
}