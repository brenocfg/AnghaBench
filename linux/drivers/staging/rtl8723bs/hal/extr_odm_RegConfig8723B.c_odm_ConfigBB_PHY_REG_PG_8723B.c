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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  Adapter; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_INIT ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PHY_StoreTxPowerByRate (int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

void odm_ConfigBB_PHY_REG_PG_8723B(
	PDM_ODM_T pDM_Odm,
	u32 Band,
	u32 RfPath,
	u32 TxNum,
	u32 Addr,
	u32 Bitmask,
	u32 Data
)
{
	if (Addr == 0xfe || Addr == 0xffe)
		msleep(50);
	else {
		PHY_StoreTxPowerByRate(pDM_Odm->Adapter, Band, RfPath, TxNum, Addr, Bitmask, Data);
	}
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_INIT,
		ODM_DBG_LOUD,
		(
			"===> ODM_ConfigBBWithHeaderFile: [PHY_REG] %08X %08X %08X\n",
			Addr,
			Bitmask,
			Data
		)
	);
}