#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sdio_device_id {int dummy; } ;
struct sdio_data {TYPE_1__* func; } ;
struct net_device {int dummy; } ;
struct dvobj_priv {struct adapter* padapters; struct adapter* if1; struct sdio_data intf_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  mac_addr; } ;
struct adapter {int bDriverStopped; int /*<<< orphan*/  rtw_wdev; scalar_t__ HalData; int /*<<< orphan*/  hw_init_completed; int /*<<< orphan*/  bup; int /*<<< orphan*/  bSurpriseRemoved; TYPE_2__ eeprompriv; int /*<<< orphan*/ * intf_free_irq; int /*<<< orphan*/ * intf_alloc_irq; int /*<<< orphan*/ * intf_deinit; int /*<<< orphan*/ * intf_init; int /*<<< orphan*/ * intf_stop; int /*<<< orphan*/ * intf_start; scalar_t__ iface_id; struct dvobj_priv* dvobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  dvobj_to_dev (struct dvobj_priv*) ; 
 int /*<<< orphan*/  hal_btcoex_Initialize (void*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  rtw_free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  rtw_hal_chip_configure (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_disable_interrupt (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_read_chip_info (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_read_chip_version (struct adapter*) ; 
 int rtw_init_drv_sw (struct adapter*) ; 
 int rtw_init_io_priv (struct adapter*,int /*<<< orphan*/ ) ; 
 struct net_device* rtw_init_netdev (struct adapter*) ; 
 int /*<<< orphan*/  rtw_macaddr_cfg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct adapter* rtw_netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtw_set_hal_ops (struct adapter*) ; 
 int /*<<< orphan*/  rtw_wdev_alloc (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_wdev_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_wdev_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_intf_start ; 
 int /*<<< orphan*/  sd_intf_stop ; 
 int /*<<< orphan*/  sdio_alloc_irq ; 
 int /*<<< orphan*/  sdio_deinit ; 
 int /*<<< orphan*/  sdio_free_irq ; 
 int /*<<< orphan*/  sdio_init ; 
 int /*<<< orphan*/  sdio_set_intf_ops ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 struct adapter* vzalloc (int) ; 

__attribute__((used)) static struct adapter *rtw_sdio_if1_init(struct dvobj_priv *dvobj, const struct sdio_device_id  *pdid)
{
	int status = _FAIL;
	struct net_device *pnetdev;
	struct adapter *padapter = NULL;
	struct sdio_data *psdio = &dvobj->intf_data;

	padapter = vzalloc(sizeof(*padapter));
	if (padapter == NULL) {
		goto exit;
	}

	padapter->dvobj = dvobj;
	dvobj->if1 = padapter;

	padapter->bDriverStopped =true;

	dvobj->padapters = padapter;
	padapter->iface_id = 0;

	/* 3 1. init network device data */
	pnetdev = rtw_init_netdev(padapter);
	if (!pnetdev)
		goto free_adapter;

	SET_NETDEV_DEV(pnetdev, dvobj_to_dev(dvobj));

	padapter = rtw_netdev_priv(pnetdev);

	rtw_wdev_alloc(padapter, dvobj_to_dev(dvobj));

	/* 3 3. init driver special setting, interface, OS and hardware relative */

	/* 4 3.1 set hardware operation functions */
	rtw_set_hal_ops(padapter);


	/* 3 5. initialize Chip version */
	padapter->intf_start = &sd_intf_start;
	padapter->intf_stop = &sd_intf_stop;

	padapter->intf_init = &sdio_init;
	padapter->intf_deinit = &sdio_deinit;
	padapter->intf_alloc_irq = &sdio_alloc_irq;
	padapter->intf_free_irq = &sdio_free_irq;

	if (rtw_init_io_priv(padapter, sdio_set_intf_ops) == _FAIL) {
		RT_TRACE(_module_hci_intfs_c_, _drv_err_,
			("rtw_drv_init: Can't init io_priv\n"));
		goto free_hal_data;
	}

	rtw_hal_read_chip_version(padapter);

	rtw_hal_chip_configure(padapter);

	hal_btcoex_Initialize((void *) padapter);

	/* 3 6. read efuse/eeprom data */
	rtw_hal_read_chip_info(padapter);

	/* 3 7. init driver common data */
	if (rtw_init_drv_sw(padapter) == _FAIL) {
		RT_TRACE(_module_hci_intfs_c_, _drv_err_,
			 ("rtw_drv_init: Initialize driver software resource Failed!\n"));
		goto free_hal_data;
	}

	/* 3 8. get WLan MAC address */
	/*  set mac addr */
	rtw_macaddr_cfg(&psdio->func->dev, padapter->eeprompriv.mac_addr);

	rtw_hal_disable_interrupt(padapter);

	DBG_871X("bDriverStopped:%d, bSurpriseRemoved:%d, bup:%d, hw_init_completed:%d\n"
		, padapter->bDriverStopped
		, padapter->bSurpriseRemoved
		, padapter->bup
		, padapter->hw_init_completed
	);

	status = _SUCCESS;

free_hal_data:
	if (status != _SUCCESS && padapter->HalData)
		kfree(padapter->HalData);

	if (status != _SUCCESS) {
		rtw_wdev_unregister(padapter->rtw_wdev);
		rtw_wdev_free(padapter->rtw_wdev);
	}

free_adapter:
	if (status != _SUCCESS) {
		if (pnetdev)
			rtw_free_netdev(pnetdev);
		else
			vfree((u8 *)padapter);
		padapter = NULL;
	}
exit:
	return padapter;
}