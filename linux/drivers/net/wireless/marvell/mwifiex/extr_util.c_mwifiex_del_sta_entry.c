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
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_sta_node {int /*<<< orphan*/  list; } ;
struct mwifiex_private {int /*<<< orphan*/  sta_list_spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mwifiex_sta_node*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct mwifiex_sta_node* mwifiex_get_sta_entry (struct mwifiex_private*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mwifiex_del_sta_entry(struct mwifiex_private *priv, const u8 *mac)
{
	struct mwifiex_sta_node *node;

	spin_lock_bh(&priv->sta_list_spinlock);

	node = mwifiex_get_sta_entry(priv, mac);
	if (node) {
		list_del(&node->list);
		kfree(node);
	}

	spin_unlock_bh(&priv->sta_list_spinlock);
	return;
}