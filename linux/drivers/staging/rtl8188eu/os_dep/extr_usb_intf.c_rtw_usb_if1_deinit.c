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
struct mlme_priv {int dummy; } ;
struct adapter {int /*<<< orphan*/  hw_init_completed; int /*<<< orphan*/  pmondev; struct mlme_priv mlmepriv; struct net_device* pnetdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_mlme_ap_info (struct adapter*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl88eu_mon_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_cancel_all_timer (struct adapter*) ; 
 int /*<<< orphan*/  rtw_dev_unload (struct adapter*) ; 
 int /*<<< orphan*/  rtw_disassoc_cmd (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_free_drv_sw (struct adapter*) ; 
 int /*<<< orphan*/  rtw_free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void rtw_usb_if1_deinit(struct adapter *if1)
{
	struct net_device *pnetdev = if1->pnetdev;
	struct mlme_priv *pmlmepriv = &if1->mlmepriv;

	if (check_fwstate(pmlmepriv, _FW_LINKED))
		rtw_disassoc_cmd(if1, 0, false);

#ifdef CONFIG_88EU_AP_MODE
	free_mlme_ap_info(if1);
#endif

	if (pnetdev)
		unregister_netdev(pnetdev); /* will call netdev_close() */

	rtl88eu_mon_deinit(if1->pmondev);
	rtw_cancel_all_timer(if1);

	rtw_dev_unload(if1);
	pr_debug("+r871xu_dev_remove, hw_init_completed=%d\n",
		if1->hw_init_completed);
	rtw_free_drv_sw(if1);
	rtw_free_netdev(pnetdev);
}