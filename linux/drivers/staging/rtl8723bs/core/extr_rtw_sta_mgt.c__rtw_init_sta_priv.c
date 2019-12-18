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
typedef  int /*<<< orphan*/  u32 ;
struct sta_priv {int auth_to; int assoc_to; int expire_to; int max_num_sta; scalar_t__ auth_list_cnt; scalar_t__ asoc_list_cnt; int /*<<< orphan*/  auth_list_lock; int /*<<< orphan*/  asoc_list_lock; int /*<<< orphan*/  auth_list; int /*<<< orphan*/  asoc_list; scalar_t__ tim_bitmap; scalar_t__ sta_dz_bitmap; int /*<<< orphan*/  free_sta_queue; int /*<<< orphan*/ * sta_hash; scalar_t__ pstainfo_buf; int /*<<< orphan*/  wakeup_q; int /*<<< orphan*/  sleep_q; scalar_t__ asoc_sta_count; int /*<<< orphan*/  sta_hash_lock; scalar_t__ pallocated_stainfo_buf; } ;
struct sta_info {int /*<<< orphan*/  list; } ;
typedef  int s32 ;
typedef  int SIZE_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NUM_STA ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _rtw_init_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_init_stainfo (struct sta_info*) ; 
 int /*<<< orphan*/  get_list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ vzalloc (int) ; 

u32 _rtw_init_sta_priv(struct	sta_priv *pstapriv)
{
	struct sta_info *psta;
	s32 i;

	pstapriv->pallocated_stainfo_buf = vzalloc(sizeof(struct sta_info) * NUM_STA+4);

	if (!pstapriv->pallocated_stainfo_buf)
		return _FAIL;

	pstapriv->pstainfo_buf = pstapriv->pallocated_stainfo_buf + 4 -
		((SIZE_PTR)(pstapriv->pallocated_stainfo_buf) & 3);

	_rtw_init_queue(&pstapriv->free_sta_queue);

	spin_lock_init(&pstapriv->sta_hash_lock);

	/* _rtw_init_queue(&pstapriv->asoc_q); */
	pstapriv->asoc_sta_count = 0;
	_rtw_init_queue(&pstapriv->sleep_q);
	_rtw_init_queue(&pstapriv->wakeup_q);

	psta = (struct sta_info *)(pstapriv->pstainfo_buf);

	for (i = 0; i < NUM_STA; i++) {
		_rtw_init_stainfo(psta);

		INIT_LIST_HEAD(&(pstapriv->sta_hash[i]));

		list_add_tail(&psta->list, get_list_head(&pstapriv->free_sta_queue));

		psta++;
	}

	pstapriv->sta_dz_bitmap = 0;
	pstapriv->tim_bitmap = 0;

	INIT_LIST_HEAD(&pstapriv->asoc_list);
	INIT_LIST_HEAD(&pstapriv->auth_list);
	spin_lock_init(&pstapriv->asoc_list_lock);
	spin_lock_init(&pstapriv->auth_list_lock);
	pstapriv->asoc_list_cnt = 0;
	pstapriv->auth_list_cnt = 0;

	pstapriv->auth_to = 3; /*  3*2 = 6 sec */
	pstapriv->assoc_to = 3;
	pstapriv->expire_to = 3; /*  3*2 = 6 sec */
	pstapriv->max_num_sta = NUM_STA;
	return _SUCCESS;
}