#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int PhyRegPgVersion; int /*<<< orphan*/  PhyRegPgValueType; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int* Array_MP_8723B_PHY_REG_PG ; 
 int /*<<< orphan*/  ODM_COMP_INIT ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PHY_REG_PG_EXACT_VALUE ; 
 int /*<<< orphan*/  odm_ConfigBB_PHY_REG_PG_8723B (TYPE_1__*,int,int,int,int,int,int) ; 

void ODM_ReadAndConfig_MP_8723B_PHY_REG_PG(PDM_ODM_T pDM_Odm)
{
	u32 i = 0;
	u32 *Array = Array_MP_8723B_PHY_REG_PG;

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_INIT,
		ODM_DBG_LOUD,
		("===> ODM_ReadAndConfig_MP_8723B_PHY_REG_PG\n")
	);

	pDM_Odm->PhyRegPgVersion = 1;
	pDM_Odm->PhyRegPgValueType = PHY_REG_PG_EXACT_VALUE;

	for (i = 0; i < ARRAY_SIZE(Array_MP_8723B_PHY_REG_PG); i += 6) {
		u32 v1 = Array[i];
		u32 v2 = Array[i+1];
		u32 v3 = Array[i+2];
		u32 v4 = Array[i+3];
		u32 v5 = Array[i+4];
		u32 v6 = Array[i+5];

		odm_ConfigBB_PHY_REG_PG_8723B(pDM_Odm, v1, v2, v3, v4, v5, v6);
	}
}