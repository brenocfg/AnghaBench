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
struct rtw_dig {scalar_t__ CurIGValue; } ;
struct odm_dm_struct {struct adapter* Adapter; struct rtw_dig DM_DigTable; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_BIT_IGI_11N ; 
 int /*<<< orphan*/  ODM_REG_IGI_A_11N ; 
 int /*<<< orphan*/  phy_set_bb_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void ODM_Write_DIG(struct odm_dm_struct *pDM_Odm, u8 CurrentIGI)
{
	struct rtw_dig *pDM_DigTable = &pDM_Odm->DM_DigTable;
	struct adapter *adapter = pDM_Odm->Adapter;

	if (pDM_DigTable->CurIGValue != CurrentIGI) {
		phy_set_bb_reg(adapter, ODM_REG_IGI_A_11N, ODM_BIT_IGI_11N, CurrentIGI);
		pDM_DigTable->CurIGValue = CurrentIGI;
	}
}