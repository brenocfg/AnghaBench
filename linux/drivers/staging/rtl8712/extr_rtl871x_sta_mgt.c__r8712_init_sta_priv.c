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
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct sta_priv {int /*<<< orphan*/  auth_list; int /*<<< orphan*/  asoc_list; TYPE_1__ free_sta_queue; int /*<<< orphan*/ * sta_hash; scalar_t__ pstainfo_buf; TYPE_1__ wakeup_q; TYPE_1__ sleep_q; scalar_t__ asoc_sta_count; int /*<<< orphan*/  sta_hash_lock; scalar_t__ pallocated_stainfo_buf; } ;
struct sta_info {int /*<<< orphan*/  list; } ;
typedef  int s32 ;
typedef  int addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NUM_STA ; 
 int /*<<< orphan*/  _init_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  _init_stainfo (struct sta_info*) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int _r8712_init_sta_priv(struct	sta_priv *pstapriv)
{
	struct sta_info *psta;
	s32 i;

	pstapriv->pallocated_stainfo_buf = kmalloc(sizeof(struct sta_info) *
						   NUM_STA + 4, GFP_ATOMIC);
	if (!pstapriv->pallocated_stainfo_buf)
		return -ENOMEM;
	pstapriv->pstainfo_buf = pstapriv->pallocated_stainfo_buf + 4 -
		((addr_t)(pstapriv->pallocated_stainfo_buf) & 3);
	_init_queue(&pstapriv->free_sta_queue);
	spin_lock_init(&pstapriv->sta_hash_lock);
	pstapriv->asoc_sta_count = 0;
	_init_queue(&pstapriv->sleep_q);
	_init_queue(&pstapriv->wakeup_q);
	psta = (struct sta_info *)(pstapriv->pstainfo_buf);
	for (i = 0; i < NUM_STA; i++) {
		_init_stainfo(psta);
		INIT_LIST_HEAD(&(pstapriv->sta_hash[i]));
		list_add_tail(&psta->list, &pstapriv->free_sta_queue.queue);
		psta++;
	}
	INIT_LIST_HEAD(&pstapriv->asoc_list);
	INIT_LIST_HEAD(&pstapriv->auth_list);
	return 0;
}