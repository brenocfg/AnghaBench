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
typedef  scalar_t__ u8 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_APFM_ON_MAC ; 
 scalar_t__ HalPwrSeqCmdParsing (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWR_CUT_ALL_MSK ; 
 int /*<<< orphan*/  PWR_FAB_ALL_MSK ; 
 int /*<<< orphan*/  PWR_INTF_SDIO_MSK ; 
 int /*<<< orphan*/  REG_RSV_CTRL ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  rtl8723B_card_enable_flow ; 
 int /*<<< orphan*/  rtw_hal_get_hwreg (struct adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 CardEnable(struct adapter *padapter)
{
	u8 bMacPwrCtrlOn;
	u8 ret = _FAIL;


	rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
	if (!bMacPwrCtrlOn) {
		/*  RSV_CTRL 0x1C[7:0] = 0x00 */
		/*  unlock ISO/CLK/Power control register */
		rtw_write8(padapter, REG_RSV_CTRL, 0x0);

		ret = HalPwrSeqCmdParsing(padapter, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, rtl8723B_card_enable_flow);
		if (ret == _SUCCESS) {
			u8 bMacPwrCtrlOn = true;
			rtw_hal_set_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
		}
	} else
		ret = _SUCCESS;

	return ret;
}