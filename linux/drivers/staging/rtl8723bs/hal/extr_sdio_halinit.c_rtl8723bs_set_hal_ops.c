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
struct hal_ops {int /*<<< orphan*/ * hal_checke_bt_hang; int /*<<< orphan*/ * hal_cancle_checkbthang_workqueue; int /*<<< orphan*/ * hal_free_checkbthang_workqueue; int /*<<< orphan*/ * hal_init_checkbthang_workqueue; int /*<<< orphan*/ * hal_xmitframe_enqueue; int /*<<< orphan*/ * mgnt_xmit; int /*<<< orphan*/ * hal_xmit; int /*<<< orphan*/ * SetHalDefVarHandler; int /*<<< orphan*/ * GetHalDefVarHandler; int /*<<< orphan*/ * SetHwRegHandlerWithBuf; int /*<<< orphan*/ * GetHwRegHandler; int /*<<< orphan*/ * SetHwRegHandler; int /*<<< orphan*/ * clear_interrupt; int /*<<< orphan*/ * check_ips_status; int /*<<< orphan*/ * disable_interrupt; int /*<<< orphan*/ * enable_interrupt; int /*<<< orphan*/ * read_adapter_info; int /*<<< orphan*/ * intf_chip_configure; int /*<<< orphan*/ * init_default_value; int /*<<< orphan*/ * free_recv_priv; int /*<<< orphan*/ * init_recv_priv; int /*<<< orphan*/ * free_xmit_priv; int /*<<< orphan*/ * init_xmit_priv; int /*<<< orphan*/ * inirp_deinit; int /*<<< orphan*/ * inirp_init; int /*<<< orphan*/ * hal_deinit; int /*<<< orphan*/ * hal_init; } ;
struct adapter {struct hal_ops HalFunc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CheckIPSStatus ; 
 int /*<<< orphan*/  ClearInterrupt8723BSdio ; 
 int /*<<< orphan*/  DisableInterrupt8723BSdio ; 
 int /*<<< orphan*/  EnableInterrupt8723BSdio ; 
 int /*<<< orphan*/  GetHalDefVar8723BSDIO ; 
 int /*<<< orphan*/  GetHwReg8723BS ; 
 int /*<<< orphan*/  ReadAdapterInfo8723BS ; 
 int /*<<< orphan*/  SetHalDefVar8723BSDIO ; 
 int /*<<< orphan*/  SetHwReg8723BS ; 
 int /*<<< orphan*/  SetHwRegWithBuf8723B ; 
 int /*<<< orphan*/  rtl8723b_set_hal_ops (struct hal_ops*) ; 
 int /*<<< orphan*/  rtl8723bs_cancle_checkbthang_workqueue ; 
 int /*<<< orphan*/  rtl8723bs_free_checkbthang_workqueue ; 
 int /*<<< orphan*/  rtl8723bs_free_recv_priv ; 
 int /*<<< orphan*/  rtl8723bs_free_xmit_priv ; 
 int /*<<< orphan*/  rtl8723bs_hal_check_bt_hang ; 
 int /*<<< orphan*/  rtl8723bs_hal_deinit ; 
 int /*<<< orphan*/  rtl8723bs_hal_init ; 
 int /*<<< orphan*/  rtl8723bs_hal_xmit ; 
 int /*<<< orphan*/  rtl8723bs_hal_xmitframe_enqueue ; 
 int /*<<< orphan*/  rtl8723bs_inirp_deinit ; 
 int /*<<< orphan*/  rtl8723bs_inirp_init ; 
 int /*<<< orphan*/  rtl8723bs_init_checkbthang_workqueue ; 
 int /*<<< orphan*/  rtl8723bs_init_default_value ; 
 int /*<<< orphan*/  rtl8723bs_init_recv_priv ; 
 int /*<<< orphan*/  rtl8723bs_init_xmit_priv ; 
 int /*<<< orphan*/  rtl8723bs_interface_configure ; 
 int /*<<< orphan*/  rtl8723bs_mgnt_xmit ; 

void rtl8723bs_set_hal_ops(struct adapter *padapter)
{
	struct hal_ops *pHalFunc = &padapter->HalFunc;

	rtl8723b_set_hal_ops(pHalFunc);

	pHalFunc->hal_init = &rtl8723bs_hal_init;
	pHalFunc->hal_deinit = &rtl8723bs_hal_deinit;

	pHalFunc->inirp_init = &rtl8723bs_inirp_init;
	pHalFunc->inirp_deinit = &rtl8723bs_inirp_deinit;

	pHalFunc->init_xmit_priv = &rtl8723bs_init_xmit_priv;
	pHalFunc->free_xmit_priv = &rtl8723bs_free_xmit_priv;

	pHalFunc->init_recv_priv = &rtl8723bs_init_recv_priv;
	pHalFunc->free_recv_priv = &rtl8723bs_free_recv_priv;

	pHalFunc->init_default_value = &rtl8723bs_init_default_value;
	pHalFunc->intf_chip_configure = &rtl8723bs_interface_configure;
	pHalFunc->read_adapter_info = &ReadAdapterInfo8723BS;

	pHalFunc->enable_interrupt = &EnableInterrupt8723BSdio;
	pHalFunc->disable_interrupt = &DisableInterrupt8723BSdio;
	pHalFunc->check_ips_status = &CheckIPSStatus;
#ifdef CONFIG_WOWLAN
	pHalFunc->clear_interrupt = &ClearInterrupt8723BSdio;
#endif
	pHalFunc->SetHwRegHandler = &SetHwReg8723BS;
	pHalFunc->GetHwRegHandler = &GetHwReg8723BS;
	pHalFunc->SetHwRegHandlerWithBuf = &SetHwRegWithBuf8723B;
	pHalFunc->GetHalDefVarHandler = &GetHalDefVar8723BSDIO;
	pHalFunc->SetHalDefVarHandler = &SetHalDefVar8723BSDIO;

	pHalFunc->hal_xmit = &rtl8723bs_hal_xmit;
	pHalFunc->mgnt_xmit = &rtl8723bs_mgnt_xmit;
	pHalFunc->hal_xmitframe_enqueue = &rtl8723bs_hal_xmitframe_enqueue;

#if defined(CONFIG_CHECK_BT_HANG)
	pHalFunc->hal_init_checkbthang_workqueue = &rtl8723bs_init_checkbthang_workqueue;
	pHalFunc->hal_free_checkbthang_workqueue = &rtl8723bs_free_checkbthang_workqueue;
	pHalFunc->hal_cancle_checkbthang_workqueue = &rtl8723bs_cancle_checkbthang_workqueue;
	pHalFunc->hal_checke_bt_hang = &rtl8723bs_hal_check_bt_hang;
#endif
}