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
struct net_device {int watchdog_timeo; struct iw_handler_def* wireless_handlers; int /*<<< orphan*/ * netdev_ops; } ;
struct iw_handler_def {int dummy; } ;
struct adapter {struct net_device* pnetdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int HZ ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 int /*<<< orphan*/  loadparam (struct adapter*,struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,struct net_device*) ; 
 struct net_device* rtw_alloc_etherdev (int) ; 
 struct net_device* rtw_alloc_etherdev_with_old_priv (int,void*) ; 
 int /*<<< orphan*/  rtw_handlers_def ; 
 int /*<<< orphan*/  rtw_netdev_ops ; 
 struct adapter* rtw_netdev_priv (struct net_device*) ; 

struct net_device *rtw_init_netdev(struct adapter *old_padapter)
{
	struct adapter *padapter;
	struct net_device *pnetdev;

	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("+init_net_dev\n"));

	if (old_padapter != NULL)
		pnetdev = rtw_alloc_etherdev_with_old_priv(sizeof(struct adapter), (void *)old_padapter);
	else
		pnetdev = rtw_alloc_etherdev(sizeof(struct adapter));

	pr_info("pnetdev = %p\n", pnetdev);
	if (!pnetdev)
		return NULL;

	padapter = rtw_netdev_priv(pnetdev);
	padapter->pnetdev = pnetdev;

	/* pnetdev->init = NULL; */

	DBG_871X("register rtw_netdev_ops to netdev_ops\n");
	pnetdev->netdev_ops = &rtw_netdev_ops;

	/* pnetdev->tx_timeout = NULL; */
	pnetdev->watchdog_timeo = HZ * 3; /* 3 second timeout */
	pnetdev->wireless_handlers = (struct iw_handler_def *)&rtw_handlers_def;

	/* step 2. */
	loadparam(padapter, pnetdev);

	return pnetdev;
}