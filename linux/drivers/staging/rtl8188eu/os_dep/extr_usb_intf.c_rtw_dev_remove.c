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
struct usb_interface {int /*<<< orphan*/  unregistering; } ;
struct dvobj_priv {struct adapter* if1; } ;
struct adapter {int bSurpriseRemoved; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_NONE ; 
 int /*<<< orphan*/  LeaveAllPowerSaveMode (struct adapter*) ; 
 int /*<<< orphan*/  PS_MODE_ACTIVE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  rtw_pm_set_ips (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_pm_set_lps (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_usb_if1_deinit (struct adapter*) ; 
 int /*<<< orphan*/  usb_dvobj_deinit (struct usb_interface*) ; 
 struct dvobj_priv* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void rtw_dev_remove(struct usb_interface *pusb_intf)
{
	struct dvobj_priv *dvobj = usb_get_intfdata(pusb_intf);
	struct adapter *padapter = dvobj->if1;

	pr_debug("+rtw_dev_remove\n");
	RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("+dev_remove()\n"));

	if (!pusb_intf->unregistering)
		padapter->bSurpriseRemoved = true;

	rtw_pm_set_ips(padapter, IPS_NONE);
	rtw_pm_set_lps(padapter, PS_MODE_ACTIVE);

	LeaveAllPowerSaveMode(padapter);

	rtw_usb_if1_deinit(padapter);

	usb_dvobj_deinit(pusb_intf);

	RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("-dev_remove()\n"));
	pr_debug("-r871xu_dev_remove, done\n");
}