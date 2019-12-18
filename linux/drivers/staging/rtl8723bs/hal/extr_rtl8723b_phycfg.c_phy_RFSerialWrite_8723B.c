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
typedef  int u32 ;
struct hal_com_data {struct bb_register_def* PHYRegDef; } ;
struct bb_register_def {int /*<<< orphan*/  rf3wireOffset; } ;
struct adapter {int dummy; } ;
typedef  enum RF_PATH { ____Placeholder_RF_PATH } RF_PATH ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  PHY_SetBBReg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bMaskDWord ; 

__attribute__((used)) static void phy_RFSerialWrite_8723B(
	struct adapter *Adapter,
	enum RF_PATH eRFPath,
	u32 Offset,
	u32 Data
)
{
	u32 DataAndAddr = 0;
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	struct bb_register_def *pPhyReg = &pHalData->PHYRegDef[eRFPath];
	u32 NewOffset;

	Offset &= 0xff;

	/*  */
	/*  Switch page for 8256 RF IC */
	/*  */
	NewOffset = Offset;

	/*  */
	/*  Put write addr in [5:0]  and write data in [31:16] */
	/*  */
	/* DataAndAddr = (Data<<16) | (NewOffset&0x3f); */
	DataAndAddr = ((NewOffset<<20) | (Data&0x000fffff)) & 0x0fffffff;	/*  T65 RF */

	/*  */
	/*  Write Operation */
	/*  */
	PHY_SetBBReg(Adapter, pPhyReg->rf3wireOffset, bMaskDWord, DataAndAddr);
	/* RTPRINT(FPHY, PHY_RFW, ("RFW-%d Addr[0x%lx]= 0x%lx\n", eRFPath, pPhyReg->rf3wireOffset, DataAndAddr)); */

}