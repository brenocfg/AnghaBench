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
typedef  int /*<<< orphan*/  u8 ;
struct odm_phy_info {int dummy; } ;
struct odm_packet_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  RSSI_test; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  odm_Process_RSSIForDM (TYPE_1__*,struct odm_phy_info*,struct odm_packet_info*) ; 
 int /*<<< orphan*/  odm_RxPhyStatus92CSeries_Parsing (TYPE_1__*,struct odm_phy_info*,int /*<<< orphan*/ *,struct odm_packet_info*) ; 

__attribute__((used)) static void ODM_PhyStatusQuery_92CSeries(
	PDM_ODM_T pDM_Odm,
	struct odm_phy_info *pPhyInfo,
	u8 *pPhyStatus,
	struct odm_packet_info *pPktinfo
)
{

	odm_RxPhyStatus92CSeries_Parsing(pDM_Odm, pPhyInfo, pPhyStatus, pPktinfo);

	if (!pDM_Odm->RSSI_test)
		odm_Process_RSSIForDM(pDM_Odm, pPhyInfo, pPktinfo);
}