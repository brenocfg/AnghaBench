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
struct false_alarm_stats {int Cnt_Cck_fail; } ;
struct odm_dm_struct {int SupportAbility; int RSSI_Min; scalar_t__ bLinked; scalar_t__ ExtLNA; struct false_alarm_stats FalseAlmCnt; } ;

/* Variables and functions */
 int ODM_BB_CCK_PD ; 
 int ODM_BB_FA_CNT ; 
 int /*<<< orphan*/  ODM_Write_CCK_CCA_Thres (struct odm_dm_struct*,int) ; 

void odm_CCKPacketDetectionThresh(struct odm_dm_struct *pDM_Odm)
{
	u8 CurCCK_CCAThres;
	struct false_alarm_stats *FalseAlmCnt = &(pDM_Odm->FalseAlmCnt);

	if (!(pDM_Odm->SupportAbility & (ODM_BB_CCK_PD|ODM_BB_FA_CNT)))
		return;
	if (pDM_Odm->ExtLNA)
		return;
	if (pDM_Odm->bLinked) {
		if (pDM_Odm->RSSI_Min > 25) {
			CurCCK_CCAThres = 0xcd;
		} else if ((pDM_Odm->RSSI_Min <= 25) && (pDM_Odm->RSSI_Min > 10)) {
			CurCCK_CCAThres = 0x83;
		} else {
			if (FalseAlmCnt->Cnt_Cck_fail > 1000)
				CurCCK_CCAThres = 0x83;
			else
				CurCCK_CCAThres = 0x40;
		}
	} else {
		if (FalseAlmCnt->Cnt_Cck_fail > 1000)
			CurCCK_CCAThres = 0x83;
		else
			CurCCK_CCAThres = 0x40;
	}
	ODM_Write_CCK_CCA_Thres(pDM_Odm, CurCCK_CCAThres);
}