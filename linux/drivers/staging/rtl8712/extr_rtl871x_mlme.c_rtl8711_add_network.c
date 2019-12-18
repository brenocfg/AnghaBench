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
struct wlan_bssid_ex {int dummy; } ;
struct __queue {int /*<<< orphan*/  lock; } ;
struct mlme_priv {struct __queue scanned_queue; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_current_network (struct _adapter*,struct wlan_bssid_ex*) ; 
 int /*<<< orphan*/  update_scanned_network (struct _adapter*,struct wlan_bssid_ex*) ; 

__attribute__((used)) static void rtl8711_add_network(struct _adapter *adapter,
			 struct wlan_bssid_ex *pnetwork)
{
	unsigned long irqL;
	struct mlme_priv *pmlmepriv = &(((struct _adapter *)adapter)->mlmepriv);
	struct  __queue *queue = &pmlmepriv->scanned_queue;

	spin_lock_irqsave(&queue->lock, irqL);
	update_current_network(adapter, pnetwork);
	update_scanned_network(adapter, pnetwork);
	spin_unlock_irqrestore(&queue->lock, irqL);
}