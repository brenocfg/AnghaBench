#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  Adapter; } ;
typedef  TYPE_1__* PDM_ODM_T ;
typedef  int /*<<< orphan*/  ODM_RF_RADIO_PATH_E ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_INIT ; 
 int /*<<< orphan*/  ODM_DBG_TRACE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int PHY_QueryRFReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_SetRFReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  bRFRegOffsetMask ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void odm_ConfigRFReg_8723B(
	PDM_ODM_T pDM_Odm,
	u32 Addr,
	u32 Data,
	ODM_RF_RADIO_PATH_E RF_PATH,
	u32 RegAddr
)
{
	if (Addr == 0xfe || Addr == 0xffe)
		msleep(50);
	else {
		PHY_SetRFReg(pDM_Odm->Adapter, RF_PATH, RegAddr, bRFRegOffsetMask, Data);
		/*  Add 1us delay between BB/RF register setting. */
		udelay(1);

		/* For disable/enable test in high temperature, the B6 value will fail to fill. Suggestion by BB Stanley, 2013.06.25. */
		if (Addr == 0xb6) {
			u32 getvalue = 0;
			u8 count = 0;

			getvalue = PHY_QueryRFReg(
				pDM_Odm->Adapter, RF_PATH, Addr, bMaskDWord
			);

			udelay(1);

			while ((getvalue>>8) != (Data>>8)) {
				count++;
				PHY_SetRFReg(pDM_Odm->Adapter, RF_PATH, RegAddr, bRFRegOffsetMask, Data);
				udelay(1);
				getvalue = PHY_QueryRFReg(pDM_Odm->Adapter, RF_PATH, Addr, bMaskDWord);
				ODM_RT_TRACE(
					pDM_Odm,
					ODM_COMP_INIT,
					ODM_DBG_TRACE,
					(
						"===> ODM_ConfigRFWithHeaderFile: [B6] getvalue 0x%x, Data 0x%x, count %d\n",
						getvalue,
						Data,
						count
					)
				);
				if (count > 5)
					break;
			}
		}

		if (Addr == 0xb2) {
			u32 getvalue = 0;
			u8 count = 0;

			getvalue = PHY_QueryRFReg(
				pDM_Odm->Adapter, RF_PATH, Addr, bMaskDWord
			);

			udelay(1);

			while (getvalue != Data) {
				count++;
				PHY_SetRFReg(
					pDM_Odm->Adapter,
					RF_PATH,
					RegAddr,
					bRFRegOffsetMask,
					Data
				);
				udelay(1);
				/* Do LCK againg */
				PHY_SetRFReg(
					pDM_Odm->Adapter,
					RF_PATH,
					0x18,
					bRFRegOffsetMask,
					0x0fc07
				);
				udelay(1);
				getvalue = PHY_QueryRFReg(
					pDM_Odm->Adapter, RF_PATH, Addr, bMaskDWord
				);
				ODM_RT_TRACE(
					pDM_Odm,
					ODM_COMP_INIT,
					ODM_DBG_TRACE,
					(
						"===> ODM_ConfigRFWithHeaderFile: [B2] getvalue 0x%x, Data 0x%x, count %d\n",
						getvalue,
						Data,
						count
					)
				);

				if (count > 5)
					break;
			}
		}
	}
}