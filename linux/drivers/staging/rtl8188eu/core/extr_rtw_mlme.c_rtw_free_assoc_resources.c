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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct mlme_priv {TYPE_1__ scanned_queue; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_free_assoc_resources_locked (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rtw_free_assoc_resources(struct adapter *adapter)
{
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;

	spin_lock_bh(&pmlmepriv->scanned_queue.lock);
	rtw_free_assoc_resources_locked(adapter);
	spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
}