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
typedef  size_t u32 ;
struct pm8001_phy {int /*<<< orphan*/  phy_state; } ;
struct pm8001_hba_info {struct pm8001_phy* phy; } ;
struct phy_stop_resp {int /*<<< orphan*/  phyid; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_LINK_DISABLE ; 
 size_t PHY_STOP_ERR_DEVICE_ATTACHED ; 
 size_t PHY_STOP_SUCCESS ; 
 int /*<<< orphan*/  PM8001_MSG_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,size_t,size_t) ; 

__attribute__((used)) static int mpi_phy_stop_resp(struct pm8001_hba_info *pm8001_ha, void *piomb)
{
	struct phy_stop_resp *pPayload =
		(struct phy_stop_resp *)(piomb + 4);
	u32 status =
		le32_to_cpu(pPayload->status);
	u32 phyid =
		le32_to_cpu(pPayload->phyid) & 0xFF;
	struct pm8001_phy *phy = &pm8001_ha->phy[phyid];
	PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("phy:0x%x status:0x%x\n",
					phyid, status));
	if (status == PHY_STOP_SUCCESS ||
		status == PHY_STOP_ERR_DEVICE_ATTACHED)
		phy->phy_state = PHY_LINK_DISABLE;
	return 0;
}