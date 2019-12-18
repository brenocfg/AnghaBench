#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int needs_remote_wakeup; int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct hal_data_8188e {int dummy; } ;
struct dvobj_priv {TYPE_2__* pusbdev; struct adapter* if1; } ;
struct TYPE_8__ {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  ifname; scalar_t__ monitor_enable; } ;
struct TYPE_5__ {scalar_t__ bSupportRemoteWakeup; } ;
struct adapter {int bDriverStopped; int /*<<< orphan*/  HalData; int /*<<< orphan*/  hw_init_completed; int /*<<< orphan*/  bup; int /*<<< orphan*/  bSurpriseRemoved; TYPE_4__ eeprompriv; TYPE_3__ registrypriv; TYPE_1__ pwrctrlpriv; struct net_device* pmondev; int /*<<< orphan*/  hw_init_mutex; struct dvobj_priv* dvobj; } ;
struct TYPE_6__ {int do_remote_wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_may_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvobj_to_dev (struct dvobj_priv*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 scalar_t__ register_netdev (struct net_device*) ; 
 struct net_device* rtl88eu_mon_init () ; 
 int /*<<< orphan*/  rtw_free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  rtw_hal_chip_configure (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_read_chip_info (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_read_chip_version (struct adapter*) ; 
 int rtw_init_drv_sw (struct adapter*) ; 
 struct net_device* rtw_init_netdev (struct adapter*) ; 
 int /*<<< orphan*/  rtw_init_netdev_name (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_macaddr_cfg (int /*<<< orphan*/ ) ; 
 struct adapter* rtw_netdev_priv (struct net_device*) ; 
 scalar_t__ usb_autopm_get_interface (struct usb_interface*) ; 
 int /*<<< orphan*/  vfree (struct adapter*) ; 
 struct adapter* vzalloc (int) ; 

__attribute__((used)) static struct adapter *rtw_usb_if1_init(struct dvobj_priv *dvobj,
	struct usb_interface *pusb_intf, const struct usb_device_id *pdid)
{
	struct adapter *padapter = NULL;
	struct net_device *pnetdev = NULL;
	struct net_device *pmondev;
	int status = _FAIL;

	padapter = vzalloc(sizeof(*padapter));
	if (!padapter)
		goto exit;
	padapter->dvobj = dvobj;
	dvobj->if1 = padapter;

	padapter->bDriverStopped = true;
	mutex_init(&padapter->hw_init_mutex);

	pnetdev = rtw_init_netdev(padapter);
	if (!pnetdev)
		goto free_adapter;
	SET_NETDEV_DEV(pnetdev, dvobj_to_dev(dvobj));
	padapter = rtw_netdev_priv(pnetdev);

	if (padapter->registrypriv.monitor_enable) {
		pmondev = rtl88eu_mon_init();
		if (!pmondev)
			netdev_warn(pnetdev, "Failed to initialize monitor interface");
		padapter->pmondev = pmondev;
	}

	padapter->HalData = kzalloc(sizeof(struct hal_data_8188e), GFP_KERNEL);
	if (!padapter->HalData) {
		DBG_88E("Failed to allocate memory for HAL data\n");
		goto free_adapter;
	}

	/* step read_chip_version */
	rtw_hal_read_chip_version(padapter);

	/* step usb endpoint mapping */
	rtw_hal_chip_configure(padapter);

	/* step read efuse/eeprom data and get mac_addr */
	rtw_hal_read_chip_info(padapter);

	/* step 5. */
	if (rtw_init_drv_sw(padapter) == _FAIL) {
		RT_TRACE(_module_hci_intfs_c_, _drv_err_,
			 ("Initialize driver software resource Failed!\n"));
		goto free_hal_data;
	}

#ifdef CONFIG_PM
	if (padapter->pwrctrlpriv.bSupportRemoteWakeup) {
		dvobj->pusbdev->do_remote_wakeup = 1;
		pusb_intf->needs_remote_wakeup = 1;
		device_init_wakeup(&pusb_intf->dev, 1);
		pr_debug("\n  padapter->pwrctrlpriv.bSupportRemoteWakeup~~~~~~\n");
		pr_debug("\n  padapter->pwrctrlpriv.bSupportRemoteWakeup~~~[%d]~~~\n",
			device_may_wakeup(&pusb_intf->dev));
	}
#endif

	/* 2012-07-11 Move here to prevent the 8723AS-VAU BT auto
	 * suspend influence */
	if (usb_autopm_get_interface(pusb_intf) < 0)
		pr_debug("can't get autopm:\n");

	/*  alloc dev name after read efuse. */
	rtw_init_netdev_name(pnetdev, padapter->registrypriv.ifname);
	rtw_macaddr_cfg(padapter->eeprompriv.mac_addr);
	memcpy(pnetdev->dev_addr, padapter->eeprompriv.mac_addr, ETH_ALEN);
	pr_debug("MAC Address from pnetdev->dev_addr =  %pM\n",
		pnetdev->dev_addr);

	/* step 6. Tell the network stack we exist */
	if (register_netdev(pnetdev) != 0) {
		RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("register_netdev() failed\n"));
		goto free_hal_data;
	}

	pr_debug("bDriverStopped:%d, bSurpriseRemoved:%d, bup:%d, hw_init_completed:%d\n"
		, padapter->bDriverStopped
		, padapter->bSurpriseRemoved
		, padapter->bup
		, padapter->hw_init_completed
	);

	status = _SUCCESS;

free_hal_data:
	if (status != _SUCCESS)
		kfree(padapter->HalData);
free_adapter:
	if (status != _SUCCESS) {
		if (pnetdev)
			rtw_free_netdev(pnetdev);
		else
			vfree(padapter);
		padapter = NULL;
	}
exit:
	return padapter;
}