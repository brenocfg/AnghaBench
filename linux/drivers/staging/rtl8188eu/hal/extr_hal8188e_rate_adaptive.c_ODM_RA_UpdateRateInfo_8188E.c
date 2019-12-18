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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct odm_ra_info {size_t RateID; size_t SGIEnable; int /*<<< orphan*/  RateMask; } ;
struct odm_dm_struct {struct odm_ra_info* RAInfo; } ;

/* Variables and functions */
 size_t ASSOCIATE_ENTRY_NUM ; 
 int /*<<< orphan*/  ODM_COMP_RATE_ADAPTIVE ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  odm_ARFBRefresh_8188E (struct odm_dm_struct*,struct odm_ra_info*) ; 

void ODM_RA_UpdateRateInfo_8188E(struct odm_dm_struct *dm_odm, u8 macid, u8 RateID, u32 RateMask, u8 SGIEnable)
{
	struct odm_ra_info *pRaInfo = NULL;

	if ((!dm_odm) || (macid >= ASSOCIATE_ENTRY_NUM))
		return;
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("macid =%d RateID = 0x%x RateMask = 0x%x SGIEnable =%d\n",
		     macid, RateID, RateMask, SGIEnable));

	pRaInfo = &dm_odm->RAInfo[macid];
	pRaInfo->RateID = RateID;
	pRaInfo->RateMask = RateMask;
	pRaInfo->SGIEnable = SGIEnable;
	odm_ARFBRefresh_8188E(dm_odm, pRaInfo);
}