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
typedef  int u32 ;
struct set_phy_profile_req {int ppc_phyid; void** reserved; void* tag; } ;
struct pm8001_hba_info {struct inbound_queue_table* inbnd_q_tbl; } ;
struct inbound_queue_table {int dummy; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int OPC_INB_SET_PHY_PROFILE ; 
 int /*<<< orphan*/  PHY_DWORD_LENGTH ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (struct set_phy_profile_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,int,struct set_phy_profile_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int pm8001_tag_alloc (struct pm8001_hba_info*,int*) ; 
 int /*<<< orphan*/  pm8001_tag_free (struct pm8001_hba_info*,int) ; 

void mpi_set_phy_profile_req(struct pm8001_hba_info *pm8001_ha,
	u32 operation, u32 phyid, u32 length, u32 *buf)
{
	u32 tag , i, j = 0;
	int rc;
	struct set_phy_profile_req payload;
	struct inbound_queue_table *circularQ;
	u32 opc = OPC_INB_SET_PHY_PROFILE;

	memset(&payload, 0, sizeof(payload));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	if (rc)
		PM8001_FAIL_DBG(pm8001_ha, pm8001_printk("Invalid tag\n"));
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(tag);
	payload.ppc_phyid = (((operation & 0xF) << 8) | (phyid  & 0xFF));
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk(" phy profile command for phy %x ,length is %d\n",
			payload.ppc_phyid, length));
	for (i = length; i < (length + PHY_DWORD_LENGTH - 1); i++) {
		payload.reserved[j] =  cpu_to_le32(*((u32 *)buf + i));
		j++;
	}
	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload, 0);
	if (rc)
		pm8001_tag_free(pm8001_ha, tag);
}