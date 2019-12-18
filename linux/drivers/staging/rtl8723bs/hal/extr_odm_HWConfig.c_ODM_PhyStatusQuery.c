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
struct odm_phy_info {int dummy; } ;
struct odm_packet_info {int dummy; } ;
typedef  int /*<<< orphan*/  PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_PhyStatusQuery_92CSeries (int /*<<< orphan*/ ,struct odm_phy_info*,int /*<<< orphan*/ *,struct odm_packet_info*) ; 

void ODM_PhyStatusQuery(
	PDM_ODM_T pDM_Odm,
	struct odm_phy_info *pPhyInfo,
	u8 *pPhyStatus,
	struct odm_packet_info *pPktinfo
)
{

	ODM_PhyStatusQuery_92CSeries(pDM_Odm, pPhyInfo, pPhyStatus, pPktinfo);
}