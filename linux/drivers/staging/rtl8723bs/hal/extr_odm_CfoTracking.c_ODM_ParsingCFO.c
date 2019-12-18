#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct odm_packet_info {scalar_t__ station_id; } ;
typedef  scalar_t__ s8 ;
struct TYPE_4__ {int* CFO_tail; int packetCount; } ;
struct TYPE_3__ {int SupportAbility; TYPE_2__ DM_CfoTrack; } ;
typedef  TYPE_1__* PDM_ODM_T ;
typedef  TYPE_2__* PCFO_TRACKING ;

/* Variables and functions */
 int ODM_BB_CFO_TRACKING ; 
 size_t ODM_RF_PATH_A ; 
 size_t ODM_RF_PATH_B ; 

void ODM_ParsingCFO(void *pDM_VOID, void *pPktinfo_VOID, s8 *pcfotail)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	struct odm_packet_info *pPktinfo = (struct odm_packet_info *)pPktinfo_VOID;
	PCFO_TRACKING pCfoTrack = &pDM_Odm->DM_CfoTrack;
	u8 i;

	if (!(pDM_Odm->SupportAbility & ODM_BB_CFO_TRACKING))
		return;

	if (pPktinfo->station_id != 0) {
		/* 3 Update CFO report for path-A & path-B */
		/*  Only paht-A and path-B have CFO tail and short CFO */
		for (i = ODM_RF_PATH_A; i <= ODM_RF_PATH_B; i++)
			pCfoTrack->CFO_tail[i] = (int)pcfotail[i];

		/* 3 Update packet counter */
		if (pCfoTrack->packetCount == 0xffffffff)
			pCfoTrack->packetCount = 0;
		else
			pCfoTrack->packetCount++;
	}
}