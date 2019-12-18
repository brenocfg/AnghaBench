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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  rf_pwrstate; } ;
struct adapter {TYPE_2__* HalData; TYPE_1__ pwrctrlpriv; } ;
struct TYPE_4__ {int CurAntenna; int bMacPwrCtrlOn; int /*<<< orphan*/  EfuseUsedBytes; int /*<<< orphan*/  BasicRateSet; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
#define  HW_VAR_APFM_ON_MAC 135 
#define  HW_VAR_BASIC_RATE 134 
#define  HW_VAR_BCN_VALID 133 
#define  HW_VAR_CHK_HI_QUEUE_EMPTY 132 
#define  HW_VAR_CURRENT_ANTENNA 131 
#define  HW_VAR_EFUSE_BYTES 130 
#define  HW_VAR_FWLPS_RF_ON 129 
#define  HW_VAR_TXPAUSE 128 
 int /*<<< orphan*/  REG_HGQ_INFORMATION ; 
 int /*<<< orphan*/  REG_RCR ; 
 int /*<<< orphan*/  REG_TDECTRL ; 
 int /*<<< orphan*/  REG_TXPAUSE ; 
 int /*<<< orphan*/  rf_off ; 
 int usb_read32 (struct adapter*,int /*<<< orphan*/ ) ; 
 int usb_read8 (struct adapter*,int /*<<< orphan*/ ) ; 

void rtw_hal_get_hwreg(struct adapter *Adapter, u8 variable, u8 *val)
{
	switch (variable) {
	case HW_VAR_BASIC_RATE:
		*((u16 *)(val)) = Adapter->HalData->BasicRateSet;
		/* fall through */
	case HW_VAR_TXPAUSE:
		val[0] = usb_read8(Adapter, REG_TXPAUSE);
		break;
	case HW_VAR_BCN_VALID:
		/* BCN_VALID, BIT16 of REG_TDECTRL = BIT0 of REG_TDECTRL+2 */
		val[0] = (BIT(0) & usb_read8(Adapter, REG_TDECTRL + 2)) ? true : false;
		break;
	case HW_VAR_FWLPS_RF_ON:
		{
			/* When we halt NIC, we should check if FW LPS is leave. */
			if (Adapter->pwrctrlpriv.rf_pwrstate == rf_off) {
				/*  If it is in HW/SW Radio OFF or IPS state, we do not check Fw LPS Leave, */
				/*  because Fw is unload. */
				val[0] = true;
			} else {
				u32 valRCR;

				valRCR = usb_read32(Adapter, REG_RCR);
				valRCR &= 0x00070000;
				if (valRCR)
					val[0] = false;
				else
					val[0] = true;
			}
		}
		break;
	case HW_VAR_CURRENT_ANTENNA:
		val[0] = Adapter->HalData->CurAntenna;
		break;
	case HW_VAR_EFUSE_BYTES: /*  To get EFUE total used bytes, added by Roger, 2008.12.22. */
		*((u16 *)(val)) = Adapter->HalData->EfuseUsedBytes;
		break;
	case HW_VAR_APFM_ON_MAC:
		*val = Adapter->HalData->bMacPwrCtrlOn;
		break;
	case HW_VAR_CHK_HI_QUEUE_EMPTY:
		*val = ((usb_read32(Adapter, REG_HGQ_INFORMATION) & 0x0000ff00) == 0) ? true : false;
		break;
	default:
		break;
	}
}