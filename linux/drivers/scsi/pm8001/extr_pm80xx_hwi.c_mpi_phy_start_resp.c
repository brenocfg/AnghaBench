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
struct pm8001_phy {int /*<<< orphan*/ * enable_completion; int /*<<< orphan*/  phy_state; } ;
struct pm8001_hba_info {scalar_t__ flags; struct pm8001_phy* phy; } ;
struct phy_start_resp {int /*<<< orphan*/  phyid; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_LINK_DOWN ; 
 scalar_t__ PM8001F_RUN_TIME ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,size_t,size_t) ; 

__attribute__((used)) static int mpi_phy_start_resp(struct pm8001_hba_info *pm8001_ha, void *piomb)
{
	struct phy_start_resp *pPayload =
		(struct phy_start_resp *)(piomb + 4);
	u32 status =
		le32_to_cpu(pPayload->status);
	u32 phy_id =
		le32_to_cpu(pPayload->phyid);
	struct pm8001_phy *phy = &pm8001_ha->phy[phy_id];

	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("phy start resp status:0x%x, phyid:0x%x\n",
				status, phy_id));
	if (status == 0) {
		phy->phy_state = PHY_LINK_DOWN;
		if (pm8001_ha->flags == PM8001F_RUN_TIME &&
				phy->enable_completion != NULL)
			complete(phy->enable_completion);
	}
	return 0;

}