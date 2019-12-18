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
struct mwl8k_vif {int macid; int /*<<< orphan*/  list; } ;
struct mwl8k_priv {int macids_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwl8k_remove_vif(struct mwl8k_priv *priv, struct mwl8k_vif *vif)
{
	/* Has ieee80211_restart_hw re-added the removed interfaces? */
	if (!priv->macids_used)
		return;

	priv->macids_used &= ~(1 << vif->macid);
	list_del(&vif->list);
}