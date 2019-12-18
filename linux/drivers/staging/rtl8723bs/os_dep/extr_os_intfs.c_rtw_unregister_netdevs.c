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
struct net_device {int dummy; } ;
struct dvobj_priv {struct adapter* padapters; } ;
struct adapter {scalar_t__ DriverState; int /*<<< orphan*/  rtw_wdev; struct net_device* pnetdev; } ;

/* Variables and functions */
 scalar_t__ DRIVER_DISAPPEAR ; 
 int /*<<< orphan*/  rtw_wdev_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

void rtw_unregister_netdevs(struct dvobj_priv *dvobj)
{
	struct adapter *padapter = NULL;
	struct net_device *pnetdev = NULL;

	padapter = dvobj->padapters;

	if (padapter == NULL)
		return;

	pnetdev = padapter->pnetdev;

	if ((padapter->DriverState != DRIVER_DISAPPEAR) && pnetdev)
		unregister_netdev(pnetdev); /* will call netdev_close() */
	rtw_wdev_unregister(padapter->rtw_wdev);
}