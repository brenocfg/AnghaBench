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
struct rereg_nd_name_data {struct net_device* old_pnetdev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; } ;
struct adapter {TYPE_1__ eeprompriv; struct rereg_nd_name_data rereg_nd_name_priv; struct net_device* pnetdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  adapter_to_dvobj (struct adapter*) ; 
 int /*<<< orphan*/  dvobj_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_is_locked () ; 
 struct net_device* rtw_init_netdev (struct adapter*) ; 
 int /*<<< orphan*/  rtw_init_netdev_name (struct net_device*,char const*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

int rtw_change_ifname(struct adapter *padapter, const char *ifname)
{
	struct net_device *pnetdev;
	struct net_device *cur_pnetdev;
	struct rereg_nd_name_data *rereg_priv;
	int ret;

	if (!padapter)
		goto error;

	cur_pnetdev = padapter->pnetdev;
	rereg_priv = &padapter->rereg_nd_name_priv;

	/* free the old_pnetdev */
	if (rereg_priv->old_pnetdev) {
		free_netdev(rereg_priv->old_pnetdev);
		rereg_priv->old_pnetdev = NULL;
	}

	if (!rtnl_is_locked())
		unregister_netdev(cur_pnetdev);
	else
		unregister_netdevice(cur_pnetdev);

	rereg_priv->old_pnetdev = cur_pnetdev;

	pnetdev = rtw_init_netdev(padapter);
	if (!pnetdev)  {
		ret = -1;
		goto error;
	}

	SET_NETDEV_DEV(pnetdev, dvobj_to_dev(adapter_to_dvobj(padapter)));

	rtw_init_netdev_name(pnetdev, ifname);

	memcpy(pnetdev->dev_addr, padapter->eeprompriv.mac_addr, ETH_ALEN);

	if (!rtnl_is_locked())
		ret = register_netdev(pnetdev);
	else
		ret = register_netdevice(pnetdev);

	if (ret != 0) {
		RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("register_netdev() failed\n"));
		goto error;
	}

	return 0;

error:

	return -1;

}