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
struct net_device {struct iw_handler_def* wireless_handlers; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;
struct iw_handler_def {int dummy; } ;
struct _adapter {scalar_t__ pid; struct net_device* pnetdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 struct net_device* alloc_etherdev (int) ; 
 scalar_t__ dev_alloc_name (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifname ; 
 int /*<<< orphan*/  loadparam (struct _adapter*,struct net_device*) ; 
 struct _adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  r871x_handlers_def ; 
 int /*<<< orphan*/  rtl8712_netdev_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

struct net_device *r8712_init_netdev(void)
{
	struct _adapter *padapter;
	struct net_device *pnetdev;

	pnetdev = alloc_etherdev(sizeof(struct _adapter));
	if (!pnetdev)
		return NULL;
	if (dev_alloc_name(pnetdev, ifname) < 0) {
		strcpy(ifname, "wlan%d");
		dev_alloc_name(pnetdev, ifname);
	}
	padapter = netdev_priv(pnetdev);
	padapter->pnetdev = pnetdev;
	pr_info("r8712u: register rtl8712_netdev_ops to netdev_ops\n");
	pnetdev->netdev_ops = &rtl8712_netdev_ops;
	pnetdev->watchdog_timeo = HZ; /* 1 second timeout */
	pnetdev->wireless_handlers = (struct iw_handler_def *)
				     &r871x_handlers_def;
	loadparam(padapter, pnetdev);
	netif_carrier_off(pnetdev);
	padapter->pid = 0;  /* Initial the PID value used for HW PBC.*/
	return pnetdev;
}