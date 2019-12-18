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
struct mwifiex_sta_node {int /*<<< orphan*/  list; int /*<<< orphan*/  mac_addr; } ;
struct mwifiex_private {int /*<<< orphan*/  sta_list_spinlock; int /*<<< orphan*/  sta_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct mwifiex_sta_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct mwifiex_sta_node* mwifiex_get_sta_entry (struct mwifiex_private*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct mwifiex_sta_node *
mwifiex_add_sta_entry(struct mwifiex_private *priv, const u8 *mac)
{
	struct mwifiex_sta_node *node;

	if (!mac)
		return NULL;

	spin_lock_bh(&priv->sta_list_spinlock);
	node = mwifiex_get_sta_entry(priv, mac);
	if (node)
		goto done;

	node = kzalloc(sizeof(*node), GFP_ATOMIC);
	if (!node)
		goto done;

	memcpy(node->mac_addr, mac, ETH_ALEN);
	list_add_tail(&node->list, &priv->sta_list);

done:
	spin_unlock_bh(&priv->sta_list_spinlock);
	return node;
}