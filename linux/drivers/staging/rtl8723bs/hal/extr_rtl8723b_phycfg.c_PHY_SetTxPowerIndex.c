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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
#define  MGN_11M 147 
#define  MGN_12M 146 
#define  MGN_18M 145 
#define  MGN_1M 144 
#define  MGN_24M 143 
#define  MGN_2M 142 
#define  MGN_36M 141 
#define  MGN_48M 140 
#define  MGN_54M 139 
#define  MGN_5_5M 138 
#define  MGN_6M 137 
#define  MGN_9M 136 
#define  MGN_MCS0 135 
#define  MGN_MCS1 134 
#define  MGN_MCS2 133 
#define  MGN_MCS3 132 
#define  MGN_MCS4 131 
#define  MGN_MCS5 130 
#define  MGN_MCS6 129 
#define  MGN_MCS7 128 
 scalar_t__ ODM_RF_PATH_A ; 
 scalar_t__ ODM_RF_PATH_B ; 
 int /*<<< orphan*/  PHY_SetBBReg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hal_init_c_ ; 
 int /*<<< orphan*/  bMaskByte0 ; 
 int /*<<< orphan*/  bMaskByte1 ; 
 int /*<<< orphan*/  bMaskByte2 ; 
 int /*<<< orphan*/  bMaskByte3 ; 
 int /*<<< orphan*/  rTxAGC_A_CCK1_Mcs32 ; 
 int /*<<< orphan*/  rTxAGC_A_Mcs03_Mcs00 ; 
 int /*<<< orphan*/  rTxAGC_A_Mcs07_Mcs04 ; 
 int /*<<< orphan*/  rTxAGC_A_Rate18_06 ; 
 int /*<<< orphan*/  rTxAGC_A_Rate54_24 ; 
 int /*<<< orphan*/  rTxAGC_B_CCK11_A_CCK2_11 ; 

void PHY_SetTxPowerIndex(
	struct adapter *Adapter,
	u32 PowerIndex,
	u8 RFPath,
	u8 Rate
)
{
	if (RFPath == ODM_RF_PATH_A || RFPath == ODM_RF_PATH_B) {
		switch (Rate) {
		case MGN_1M:
			PHY_SetBBReg(Adapter, rTxAGC_A_CCK1_Mcs32, bMaskByte1, PowerIndex);
			break;
		case MGN_2M:
			PHY_SetBBReg(Adapter, rTxAGC_B_CCK11_A_CCK2_11, bMaskByte1, PowerIndex);
			break;
		case MGN_5_5M:
			PHY_SetBBReg(Adapter, rTxAGC_B_CCK11_A_CCK2_11, bMaskByte2, PowerIndex);
			break;
		case MGN_11M:
			PHY_SetBBReg(Adapter, rTxAGC_B_CCK11_A_CCK2_11, bMaskByte3, PowerIndex);
			break;

		case MGN_6M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate18_06, bMaskByte0, PowerIndex);
			break;
		case MGN_9M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate18_06, bMaskByte1, PowerIndex);
			break;
		case MGN_12M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate18_06, bMaskByte2, PowerIndex);
			break;
		case MGN_18M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate18_06, bMaskByte3, PowerIndex);
			break;

		case MGN_24M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate54_24, bMaskByte0, PowerIndex);
			break;
		case MGN_36M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate54_24, bMaskByte1, PowerIndex);
			break;
		case MGN_48M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate54_24, bMaskByte2, PowerIndex);
			break;
		case MGN_54M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate54_24, bMaskByte3, PowerIndex);
			break;

		case MGN_MCS0:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs03_Mcs00, bMaskByte0, PowerIndex);
			break;
		case MGN_MCS1:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs03_Mcs00, bMaskByte1, PowerIndex);
			break;
		case MGN_MCS2:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs03_Mcs00, bMaskByte2, PowerIndex);
			break;
		case MGN_MCS3:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs03_Mcs00, bMaskByte3, PowerIndex);
			break;

		case MGN_MCS4:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs07_Mcs04, bMaskByte0, PowerIndex);
			break;
		case MGN_MCS5:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs07_Mcs04, bMaskByte1, PowerIndex);
			break;
		case MGN_MCS6:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs07_Mcs04, bMaskByte2, PowerIndex);
			break;
		case MGN_MCS7:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs07_Mcs04, bMaskByte3, PowerIndex);
			break;

		default:
			DBG_871X("Invalid Rate!!\n");
			break;
		}
	} else {
		RT_TRACE(_module_hal_init_c_, _drv_err_, ("Invalid RFPath!!\n"));
	}
}