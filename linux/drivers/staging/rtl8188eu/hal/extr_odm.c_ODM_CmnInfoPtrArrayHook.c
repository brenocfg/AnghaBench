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
typedef  size_t u16 ;
struct sta_info {int dummy; } ;
struct odm_dm_struct {struct sta_info** pODM_StaInfo; } ;
typedef  enum odm_common_info_def { ____Placeholder_odm_common_info_def } odm_common_info_def ;

/* Variables and functions */
 int ODM_CMNINFO_STA_STATUS ; 

void ODM_CmnInfoPtrArrayHook(struct odm_dm_struct *pDM_Odm, enum odm_common_info_def CmnInfo, u16 Index, void *pValue)
{
	if (CmnInfo == ODM_CMNINFO_STA_STATUS)
		pDM_Odm->pODM_StaInfo[Index] = (struct sta_info *)pValue;
}