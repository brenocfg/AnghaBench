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
typedef  int u32 ;
struct wlan_network {unsigned long last_scanned; int /*<<< orphan*/  list; scalar_t__ fixed; } ;
struct __queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct mlme_priv {struct __queue free_bss_pool; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int SCANQUEUE_LIFETIME ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _rtw_free_network(struct mlme_priv *pmlmepriv, struct wlan_network *pnetwork, u8 isfreeall)
{
	unsigned long curr_time;
	u32 delta_time;
	u32 lifetime = SCANQUEUE_LIFETIME;
	struct __queue *free_queue = &pmlmepriv->free_bss_pool;

	if (!pnetwork)
		return;

	if (pnetwork->fixed)
		return;
	curr_time = jiffies;
	if ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) ||
	    (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)))
		lifetime = 1;
	if (!isfreeall) {
		delta_time = (curr_time - pnetwork->last_scanned)/HZ;
		if (delta_time < lifetime)/*  unit:sec */
			return;
	}
	spin_lock_bh(&free_queue->lock);
	list_del_init(&pnetwork->list);
	list_add_tail(&pnetwork->list, &free_queue->queue);
	spin_unlock_bh(&free_queue->lock);
}