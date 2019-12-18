#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct pm8001_hba_info {int /*<<< orphan*/  sas_addr; struct inbound_queue_table* inbnd_q_tbl; } ;
struct TYPE_2__ {int phy_id; int /*<<< orphan*/  sas_addr; int /*<<< orphan*/  initiator_bits; int /*<<< orphan*/  dev_type; } ;
struct phy_start_req {TYPE_1__ sas_identify; void* ase_sh_lm_slr_phyid; void* tag; } ;
struct inbound_queue_table {int dummy; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int LINKMODE_AUTO ; 
 int LINKRATE_15 ; 
 int LINKRATE_30 ; 
 int LINKRATE_60 ; 
 int OPC_INB_PHYSTART ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  SAS_END_DEVICE ; 
 int /*<<< orphan*/  SAS_PROTOCOL_ALL ; 
 int SPINHOLD_DISABLE ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct phy_start_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,int,struct phy_start_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pm8001_chip_phy_start_req(struct pm8001_hba_info *pm8001_ha, u8 phy_id)
{
	struct phy_start_req payload;
	struct inbound_queue_table *circularQ;
	int ret;
	u32 tag = 0x01;
	u32 opcode = OPC_INB_PHYSTART;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	memset(&payload, 0, sizeof(payload));
	payload.tag = cpu_to_le32(tag);
	/*
	 ** [0:7]   PHY Identifier
	 ** [8:11]  link rate 1.5G, 3G, 6G
	 ** [12:13] link mode 01b SAS mode; 10b SATA mode; 11b both
	 ** [14]    0b disable spin up hold; 1b enable spin up hold
	 */
	payload.ase_sh_lm_slr_phyid = cpu_to_le32(SPINHOLD_DISABLE |
		LINKMODE_AUTO |	LINKRATE_15 |
		LINKRATE_30 | LINKRATE_60 | phy_id);
	payload.sas_identify.dev_type = SAS_END_DEVICE;
	payload.sas_identify.initiator_bits = SAS_PROTOCOL_ALL;
	memcpy(payload.sas_identify.sas_addr,
		pm8001_ha->sas_addr, SAS_ADDR_SIZE);
	payload.sas_identify.phy_id = phy_id;
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opcode, &payload, 0);
	return ret;
}