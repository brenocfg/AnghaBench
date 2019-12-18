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
typedef  int u32 ;
struct wlan_network {int /*<<< orphan*/  list; scalar_t__ last_scanned; scalar_t__ fixed; } ;
struct __queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct mlme_priv {int /*<<< orphan*/  num_of_scanned; struct __queue free_bss_pool; } ;

/* Variables and functions */
 int HZ ; 
 int SCANQUEUE_LIFETIME ; 
 int jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void _free_network(struct mlme_priv *pmlmepriv,
			  struct wlan_network *pnetwork)
{
	u32 curr_time, delta_time;
	unsigned long irqL;
	struct  __queue *free_queue = &(pmlmepriv->free_bss_pool);

	if (!pnetwork)
		return;
	if (pnetwork->fixed)
		return;
	curr_time = jiffies;
	delta_time = (curr_time - (u32)pnetwork->last_scanned) / HZ;
	if (delta_time < SCANQUEUE_LIFETIME)
		return;
	spin_lock_irqsave(&free_queue->lock, irqL);
	list_del_init(&pnetwork->list);
	list_add_tail(&pnetwork->list, &free_queue->queue);
	pmlmepriv->num_of_scanned--;
	spin_unlock_irqrestore(&free_queue->lock, irqL);
}