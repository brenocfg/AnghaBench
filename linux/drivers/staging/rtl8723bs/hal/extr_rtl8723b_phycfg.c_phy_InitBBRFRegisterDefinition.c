#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hal_com_data {TYPE_1__* PHYRegDef; } ;
struct adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rfLSSIReadBackPi; int /*<<< orphan*/  rfLSSIReadBack; int /*<<< orphan*/  rfHSSIPara2; int /*<<< orphan*/  rf3wireOffset; void* rfintfe; void* rfintfo; void* rfintfs; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 size_t ODM_RF_PATH_A ; 
 size_t ODM_RF_PATH_B ; 
 int /*<<< orphan*/  TransceiverA_HSPI_Readback ; 
 int /*<<< orphan*/  TransceiverB_HSPI_Readback ; 
 void* rFPGA0_XAB_RFInterfaceSW ; 
 int /*<<< orphan*/  rFPGA0_XA_HSSIParameter2 ; 
 int /*<<< orphan*/  rFPGA0_XA_LSSIParameter ; 
 int /*<<< orphan*/  rFPGA0_XA_LSSIReadBack ; 
 void* rFPGA0_XA_RFInterfaceOE ; 
 int /*<<< orphan*/  rFPGA0_XB_HSSIParameter2 ; 
 int /*<<< orphan*/  rFPGA0_XB_LSSIParameter ; 
 int /*<<< orphan*/  rFPGA0_XB_LSSIReadBack ; 
 void* rFPGA0_XB_RFInterfaceOE ; 

__attribute__((used)) static void phy_InitBBRFRegisterDefinition(struct adapter *Adapter)
{
	struct hal_com_data		*pHalData = GET_HAL_DATA(Adapter);

	/*  RF Interface Sowrtware Control */
	pHalData->PHYRegDef[ODM_RF_PATH_A].rfintfs = rFPGA0_XAB_RFInterfaceSW; /*  16 LSBs if read 32-bit from 0x870 */
	pHalData->PHYRegDef[ODM_RF_PATH_B].rfintfs = rFPGA0_XAB_RFInterfaceSW; /*  16 MSBs if read 32-bit from 0x870 (16-bit for 0x872) */

	/*  RF Interface Output (and Enable) */
	pHalData->PHYRegDef[ODM_RF_PATH_A].rfintfo = rFPGA0_XA_RFInterfaceOE; /*  16 LSBs if read 32-bit from 0x860 */
	pHalData->PHYRegDef[ODM_RF_PATH_B].rfintfo = rFPGA0_XB_RFInterfaceOE; /*  16 LSBs if read 32-bit from 0x864 */

	/*  RF Interface (Output and)  Enable */
	pHalData->PHYRegDef[ODM_RF_PATH_A].rfintfe = rFPGA0_XA_RFInterfaceOE; /*  16 MSBs if read 32-bit from 0x860 (16-bit for 0x862) */
	pHalData->PHYRegDef[ODM_RF_PATH_B].rfintfe = rFPGA0_XB_RFInterfaceOE; /*  16 MSBs if read 32-bit from 0x864 (16-bit for 0x866) */

	pHalData->PHYRegDef[ODM_RF_PATH_A].rf3wireOffset = rFPGA0_XA_LSSIParameter; /* LSSI Parameter */
	pHalData->PHYRegDef[ODM_RF_PATH_B].rf3wireOffset = rFPGA0_XB_LSSIParameter;

	pHalData->PHYRegDef[ODM_RF_PATH_A].rfHSSIPara2 = rFPGA0_XA_HSSIParameter2;  /* wire control parameter2 */
	pHalData->PHYRegDef[ODM_RF_PATH_B].rfHSSIPara2 = rFPGA0_XB_HSSIParameter2;  /* wire control parameter2 */

	/*  Tranceiver Readback LSSI/HSPI mode */
	pHalData->PHYRegDef[ODM_RF_PATH_A].rfLSSIReadBack = rFPGA0_XA_LSSIReadBack;
	pHalData->PHYRegDef[ODM_RF_PATH_B].rfLSSIReadBack = rFPGA0_XB_LSSIReadBack;
	pHalData->PHYRegDef[ODM_RF_PATH_A].rfLSSIReadBackPi = TransceiverA_HSPI_Readback;
	pHalData->PHYRegDef[ODM_RF_PATH_B].rfLSSIReadBackPi = TransceiverB_HSPI_Readback;

}