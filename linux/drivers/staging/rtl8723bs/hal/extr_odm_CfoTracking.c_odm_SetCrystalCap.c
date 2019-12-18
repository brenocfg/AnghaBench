#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int CrystalCap; } ;
struct TYPE_4__ {int /*<<< orphan*/  Adapter; TYPE_2__ DM_CfoTrack; } ;
typedef  TYPE_1__* PDM_ODM_T ;
typedef  TYPE_2__* PCFO_TRACKING ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_CFO_TRACKING ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PHY_SetBBReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_MAC_PHY_CTRL ; 

__attribute__((used)) static void odm_SetCrystalCap(void *pDM_VOID, u8 CrystalCap)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	PCFO_TRACKING pCfoTrack = &pDM_Odm->DM_CfoTrack;

	if (pCfoTrack->CrystalCap == CrystalCap)
		return;

	pCfoTrack->CrystalCap = CrystalCap;

	/*  0x2C[23:18] = 0x2C[17:12] = CrystalCap */
	CrystalCap = CrystalCap & 0x3F;
	PHY_SetBBReg(
		pDM_Odm->Adapter,
		REG_MAC_PHY_CTRL,
		0x00FFF000,
		(CrystalCap | (CrystalCap << 6))
	);

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_CFO_TRACKING,
		ODM_DBG_LOUD,
		(
			"odm_SetCrystalCap(): CrystalCap = 0x%x\n",
			CrystalCap
		)
	);
}