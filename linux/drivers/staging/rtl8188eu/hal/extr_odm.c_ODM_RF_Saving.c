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
typedef  int u8 ;
struct rtl_ps {int initialize; int Reg874; int RegC70; int Reg85C; int RegA74; scalar_t__ PreRFState; scalar_t__ CurRFState; } ;
struct odm_dm_struct {int PatchID; int RSSI_Min; struct rtl_ps DM_PSTable; struct adapter* Adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ RF_MAX ; 
 scalar_t__ RF_Normal ; 
 scalar_t__ RF_Save ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int phy_query_bb_reg (struct adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_bb_reg (struct adapter*,int,int,int) ; 

void ODM_RF_Saving(struct odm_dm_struct *pDM_Odm, u8 bForceInNormal)
{
	struct adapter *adapter = pDM_Odm->Adapter;
	struct rtl_ps *pDM_PSTable = &pDM_Odm->DM_PSTable;
	u8 Rssi_Up_bound = 30;
	u8 Rssi_Low_bound = 25;

	if (pDM_Odm->PatchID == 40) { /* RT_CID_819x_FUNAI_TV */
		Rssi_Up_bound = 50;
		Rssi_Low_bound = 45;
	}
	if (pDM_PSTable->initialize == 0) {
		pDM_PSTable->Reg874 = (phy_query_bb_reg(adapter, 0x874, bMaskDWord)&0x1CC000)>>14;
		pDM_PSTable->RegC70 = (phy_query_bb_reg(adapter, 0xc70, bMaskDWord) & BIT(3))>>3;
		pDM_PSTable->Reg85C = (phy_query_bb_reg(adapter, 0x85c, bMaskDWord)&0xFF000000)>>24;
		pDM_PSTable->RegA74 = (phy_query_bb_reg(adapter, 0xa74, bMaskDWord)&0xF000)>>12;
		pDM_PSTable->initialize = 1;
	}

	if (!bForceInNormal) {
		if (pDM_Odm->RSSI_Min != 0xFF) {
			if (pDM_PSTable->PreRFState == RF_Normal) {
				if (pDM_Odm->RSSI_Min >= Rssi_Up_bound)
					pDM_PSTable->CurRFState = RF_Save;
				else
					pDM_PSTable->CurRFState = RF_Normal;
			} else {
				if (pDM_Odm->RSSI_Min <= Rssi_Low_bound)
					pDM_PSTable->CurRFState = RF_Normal;
				else
					pDM_PSTable->CurRFState = RF_Save;
			}
		} else {
			pDM_PSTable->CurRFState = RF_MAX;
		}
	} else {
		pDM_PSTable->CurRFState = RF_Normal;
	}

	if (pDM_PSTable->PreRFState != pDM_PSTable->CurRFState) {
		if (pDM_PSTable->CurRFState == RF_Save) {
			phy_set_bb_reg(adapter, 0x874, 0x1C0000, 0x2); /* Reg874[20:18]=3'b010 */
			phy_set_bb_reg(adapter, 0xc70, BIT(3), 0); /* RegC70[3]=1'b0 */
			phy_set_bb_reg(adapter, 0x85c, 0xFF000000, 0x63); /* Reg85C[31:24]=0x63 */
			phy_set_bb_reg(adapter, 0x874, 0xC000, 0x2); /* Reg874[15:14]=2'b10 */
			phy_set_bb_reg(adapter, 0xa74, 0xF000, 0x3); /* RegA75[7:4]=0x3 */
			phy_set_bb_reg(adapter, 0x818, BIT(28), 0x0); /* Reg818[28]=1'b0 */
			phy_set_bb_reg(adapter, 0x818, BIT(28), 0x1); /* Reg818[28]=1'b1 */
		} else {
			phy_set_bb_reg(adapter, 0x874, 0x1CC000, pDM_PSTable->Reg874);
			phy_set_bb_reg(adapter, 0xc70, BIT(3), pDM_PSTable->RegC70);
			phy_set_bb_reg(adapter, 0x85c, 0xFF000000, pDM_PSTable->Reg85C);
			phy_set_bb_reg(adapter, 0xa74, 0xF000, pDM_PSTable->RegA74);
			phy_set_bb_reg(adapter, 0x818, BIT(28), 0x0);
		}
		pDM_PSTable->PreRFState = pDM_PSTable->CurRFState;
	}
}