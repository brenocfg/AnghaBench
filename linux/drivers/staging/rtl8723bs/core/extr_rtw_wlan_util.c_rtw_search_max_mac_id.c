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
typedef  int u8 ;
struct dvobj_priv {int* macid; int /*<<< orphan*/  lock; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int NUM_STA ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

u8 rtw_search_max_mac_id(struct adapter *padapter)
{
	u8 max_mac_id = 0;
	struct dvobj_priv *pdvobj = adapter_to_dvobj(padapter);
	int i;
	spin_lock_bh(&pdvobj->lock);
	for (i = (NUM_STA-1); i >= 0 ; i--) {
		if (pdvobj->macid[i] == true)
			break;
	}
	max_mac_id = i;
	spin_unlock_bh(&pdvobj->lock);

	return max_mac_id;
}