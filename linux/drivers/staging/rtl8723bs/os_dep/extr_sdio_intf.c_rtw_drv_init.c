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
struct sdio_func {int dummy; } ;
struct sdio_device_id {int dummy; } ;
struct dvobj_priv {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  gpio_hostwakeup_alloc_irq (struct adapter*) ; 
 int rtw_drv_register_netdev (struct adapter*) ; 
 int /*<<< orphan*/  rtw_ndev_notifier_register () ; 
 int /*<<< orphan*/  rtw_sdio_if1_deinit (struct adapter*) ; 
 struct adapter* rtw_sdio_if1_init (struct dvobj_priv*,struct sdio_device_id const*) ; 
 int sdio_alloc_irq (struct dvobj_priv*) ; 
 int /*<<< orphan*/  sdio_dvobj_deinit (struct sdio_func*) ; 
 struct dvobj_priv* sdio_dvobj_init (struct sdio_func*) ; 

__attribute__((used)) static int rtw_drv_init(
	struct sdio_func *func,
	const struct sdio_device_id *id)
{
	int status = _FAIL;
	struct adapter *if1 = NULL, *if2 = NULL;
	struct dvobj_priv *dvobj;

	dvobj = sdio_dvobj_init(func);
	if (dvobj == NULL) {
		RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("initialize device object priv Failed!\n"));
		goto exit;
	}

	if1 = rtw_sdio_if1_init(dvobj, id);
	if (if1 == NULL) {
		DBG_871X("rtw_init_primarystruct adapter Failed!\n");
		goto free_dvobj;
	}

	/* dev_alloc_name && register_netdev */
	status = rtw_drv_register_netdev(if1);
	if (status != _SUCCESS)
		goto free_if2;

	if (sdio_alloc_irq(dvobj) != _SUCCESS)
		goto free_if2;

#ifdef	CONFIG_GPIO_WAKEUP
	gpio_hostwakeup_alloc_irq(if1);
#endif

	RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("-871x_drv - drv_init, success!\n"));

	rtw_ndev_notifier_register();
	status = _SUCCESS;

free_if2:
	if (status != _SUCCESS && if2) {
	}
	if (status != _SUCCESS && if1) {
		rtw_sdio_if1_deinit(if1);
	}
free_dvobj:
	if (status != _SUCCESS)
		sdio_dvobj_deinit(func);
exit:
	return status == _SUCCESS?0:-ENODEV;
}