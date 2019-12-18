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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int BTEfuseUsedPercentage; int BTEfuseUsedBytes; } ;
struct hal_com_data {int EfuseUsedPercentage; int EfuseUsedBytes; int bMacPwrCtrlOn; TYPE_1__ EfuseHal; } ;
struct adapter {int /*<<< orphan*/  bSurpriseRemoved; } ;
struct TYPE_4__ {int /*<<< orphan*/  rf_pwrstate; } ;

/* Variables and functions */
 int BIT (int) ; 
 int BIT7 ; 
 int BTEfuseUsedBytes ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  GetHwReg (struct adapter*,int,int*) ; 
#define  HW_VAR_APFM_ON_MAC 139 
#define  HW_VAR_BCN_VALID 138 
#define  HW_VAR_CHK_HI_QUEUE_EMPTY 137 
#define  HW_VAR_EFUSE_BT_BYTES 136 
#define  HW_VAR_EFUSE_BT_USAGE 135 
#define  HW_VAR_EFUSE_BYTES 134 
#define  HW_VAR_EFUSE_USAGE 133 
#define  HW_VAR_FWLPS_RF_ON 132 
#define  HW_VAR_RPWM_TOG 131 
#define  HW_VAR_SYS_CLKR 130 
#define  HW_VAR_TXPAUSE 129 
#define  HW_VAR_WAKEUP_REASON 128 
 int /*<<< orphan*/  REG_RCR ; 
 int REG_SYS_CLKR ; 
 int /*<<< orphan*/  REG_TDECTRL ; 
 int REG_TXPAUSE ; 
 int /*<<< orphan*/  REG_TXPKT_EMPTY ; 
 int REG_WOWLAN_WAKE_REASON ; 
 int SDIO_LOCAL_BASE ; 
 int SDIO_REG_HRPWM1 ; 
 TYPE_2__* adapter_to_pwrctl (struct adapter*) ; 
 int /*<<< orphan*/  rf_off ; 
 int rtw_read16 (struct adapter*,int /*<<< orphan*/ ) ; 
 int rtw_read32 (struct adapter*,int /*<<< orphan*/ ) ; 
 int rtw_read8 (struct adapter*,int) ; 

void GetHwReg8723B(struct adapter *padapter, u8 variable, u8 *val)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(padapter);
	u8 val8;
	u16 val16;

	switch (variable) {
	case HW_VAR_TXPAUSE:
		*val = rtw_read8(padapter, REG_TXPAUSE);
		break;

	case HW_VAR_BCN_VALID:
		{
			/*  BCN_VALID, BIT16 of REG_TDECTRL = BIT0 of REG_TDECTRL+2 */
			val8 = rtw_read8(padapter, REG_TDECTRL+2);
			*val = (BIT(0) & val8) ? true : false;
		}
		break;

	case HW_VAR_FWLPS_RF_ON:
		{
			/*  When we halt NIC, we should check if FW LPS is leave. */
			u32 valRCR;

			if (
				padapter->bSurpriseRemoved  ||
				(adapter_to_pwrctl(padapter)->rf_pwrstate == rf_off)
			) {
				/*  If it is in HW/SW Radio OFF or IPS state, we do not check Fw LPS Leave, */
				/*  because Fw is unload. */
				*val = true;
			} else {
				valRCR = rtw_read32(padapter, REG_RCR);
				valRCR &= 0x00070000;
				if (valRCR)
					*val = false;
				else
					*val = true;
			}
		}
		break;

	case HW_VAR_EFUSE_USAGE:
		*val = pHalData->EfuseUsedPercentage;
		break;

	case HW_VAR_EFUSE_BYTES:
		*((u16 *)val) = pHalData->EfuseUsedBytes;
		break;

	case HW_VAR_EFUSE_BT_USAGE:
#ifdef HAL_EFUSE_MEMORY
		*val = pHalData->EfuseHal.BTEfuseUsedPercentage;
#endif
		break;

	case HW_VAR_EFUSE_BT_BYTES:
#ifdef HAL_EFUSE_MEMORY
		*((u16 *)val) = pHalData->EfuseHal.BTEfuseUsedBytes;
#else
		*((u16 *)val) = BTEfuseUsedBytes;
#endif
		break;

	case HW_VAR_APFM_ON_MAC:
		*val = pHalData->bMacPwrCtrlOn;
		break;
	case HW_VAR_CHK_HI_QUEUE_EMPTY:
		val16 = rtw_read16(padapter, REG_TXPKT_EMPTY);
		*val = (val16 & BIT(10)) ? true:false;
		break;
#ifdef CONFIG_WOWLAN
	case HW_VAR_RPWM_TOG:
		*val = rtw_read8(padapter, SDIO_LOCAL_BASE|SDIO_REG_HRPWM1) & BIT7;
		break;
	case HW_VAR_WAKEUP_REASON:
		*val = rtw_read8(padapter, REG_WOWLAN_WAKE_REASON);
		if (*val == 0xEA)
			*val = 0;
		break;
	case HW_VAR_SYS_CLKR:
		*val = rtw_read8(padapter, REG_SYS_CLKR);
		break;
#endif
	default:
		GetHwReg(padapter, variable, val);
		break;
	}
}