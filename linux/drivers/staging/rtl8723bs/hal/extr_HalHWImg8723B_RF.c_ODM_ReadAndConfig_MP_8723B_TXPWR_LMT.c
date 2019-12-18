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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  PDM_ODM_T ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** Array_MP_8723B_TXPWR_LMT ; 
 int /*<<< orphan*/  ODM_COMP_INIT ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  odm_ConfigBB_TXPWR_LMT_8723B (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ODM_ReadAndConfig_MP_8723B_TXPWR_LMT(PDM_ODM_T pDM_Odm)
{
	u32 i = 0;
	u8 **Array = Array_MP_8723B_TXPWR_LMT;

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_INIT,
		ODM_DBG_LOUD,
		("===> ODM_ReadAndConfig_MP_8723B_TXPWR_LMT\n")
	);

	for (i = 0; i < ARRAY_SIZE(Array_MP_8723B_TXPWR_LMT); i += 7) {
		u8 *regulation = Array[i];
		u8 *band = Array[i+1];
		u8 *bandwidth = Array[i+2];
		u8 *rate = Array[i+3];
		u8 *rfPath = Array[i+4];
		u8 *chnl = Array[i+5];
		u8 *val = Array[i+6];

		odm_ConfigBB_TXPWR_LMT_8723B(
			pDM_Odm,
			regulation,
			band,
			bandwidth,
			rate,
			rfPath,
			chnl,
			val
		);
	}
}