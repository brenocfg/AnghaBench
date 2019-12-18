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
struct mwifiex_private {size_t bss_priority; struct mwifiex_adapter* adapter; } ;
struct mwifiex_bss_prio_tbl {int /*<<< orphan*/  bss_prio_lock; int /*<<< orphan*/  bss_prio_head; } ;
struct mwifiex_bss_prio_node {int /*<<< orphan*/  list; struct mwifiex_private* priv; } ;
struct mwifiex_adapter {struct mwifiex_bss_prio_tbl* bss_prio_tbl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct mwifiex_bss_prio_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mwifiex_add_bss_prio_tbl(struct mwifiex_private *priv)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	struct mwifiex_bss_prio_node *bss_prio;
	struct mwifiex_bss_prio_tbl *tbl = adapter->bss_prio_tbl;

	bss_prio = kzalloc(sizeof(struct mwifiex_bss_prio_node), GFP_KERNEL);
	if (!bss_prio)
		return -ENOMEM;

	bss_prio->priv = priv;
	INIT_LIST_HEAD(&bss_prio->list);

	spin_lock_bh(&tbl[priv->bss_priority].bss_prio_lock);
	list_add_tail(&bss_prio->list, &tbl[priv->bss_priority].bss_prio_head);
	spin_unlock_bh(&tbl[priv->bss_priority].bss_prio_lock);

	return 0;
}