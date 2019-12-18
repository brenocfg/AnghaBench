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
typedef  size_t u32 ;
struct pm8001_hba_info {TYPE_1__* phy; int /*<<< orphan*/  pdev; struct inbound_queue_table* inbnd_q_tbl; } ;
struct TYPE_4__ {size_t phy_id; int /*<<< orphan*/  sas_addr; int /*<<< orphan*/  initiator_bits; int /*<<< orphan*/  dev_type; } ;
struct phy_start_req {TYPE_2__ sas_identify; void* ase_sh_lm_slr_phyid; void* tag; } ;
struct inbound_queue_table {int dummy; } ;
typedef  int /*<<< orphan*/  payload ;
struct TYPE_3__ {int /*<<< orphan*/  dev_sas_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SPCV_12G (int /*<<< orphan*/ ) ; 
 size_t LINKMODE_AUTO ; 
 size_t LINKRATE_120 ; 
 size_t LINKRATE_15 ; 
 size_t LINKRATE_30 ; 
 size_t LINKRATE_60 ; 
 size_t OPC_INB_PHYSTART ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  SAS_END_DEVICE ; 
 int /*<<< orphan*/  SAS_PROTOCOL_ALL ; 
 size_t SPINHOLD_DISABLE ; 
 void* cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct phy_start_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,size_t,struct phy_start_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,size_t) ; 

__attribute__((used)) static int
pm80xx_chip_phy_start_req(struct pm8001_hba_info *pm8001_ha, u8 phy_id)
{
	struct phy_start_req payload;
	struct inbound_queue_table *circularQ;
	int ret;
	u32 tag = 0x01;
	u32 opcode = OPC_INB_PHYSTART;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	memset(&payload, 0, sizeof(payload));
	payload.tag = cpu_to_le32(tag);

	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("PHY START REQ for phy_id %d\n", phy_id));
	/*
	 ** [0:7]	PHY Identifier
	 ** [8:11]	link rate 1.5G, 3G, 6G
	 ** [12:13] link mode 01b SAS mode; 10b SATA mode; 11b Auto mode
	 ** [14]	0b disable spin up hold; 1b enable spin up hold
	 ** [15] ob no change in current PHY analig setup 1b enable using SPAST
	 */
	if (!IS_SPCV_12G(pm8001_ha->pdev))
		payload.ase_sh_lm_slr_phyid = cpu_to_le32(SPINHOLD_DISABLE |
				LINKMODE_AUTO | LINKRATE_15 |
				LINKRATE_30 | LINKRATE_60 | phy_id);
	else
		payload.ase_sh_lm_slr_phyid = cpu_to_le32(SPINHOLD_DISABLE |
				LINKMODE_AUTO | LINKRATE_15 |
				LINKRATE_30 | LINKRATE_60 | LINKRATE_120 |
				phy_id);

	/* SSC Disable and SAS Analog ST configuration */
	/**
	payload.ase_sh_lm_slr_phyid =
		cpu_to_le32(SSC_DISABLE_30 | SAS_ASE | SPINHOLD_DISABLE |
		LINKMODE_AUTO | LINKRATE_15 | LINKRATE_30 | LINKRATE_60 |
		phy_id);
	Have to add "SAS PHY Analog Setup SPASTI 1 Byte" Based on need
	**/

	payload.sas_identify.dev_type = SAS_END_DEVICE;
	payload.sas_identify.initiator_bits = SAS_PROTOCOL_ALL;
	memcpy(payload.sas_identify.sas_addr,
	  &pm8001_ha->phy[phy_id].dev_sas_addr, SAS_ADDR_SIZE);
	payload.sas_identify.phy_id = phy_id;
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opcode, &payload, 0);
	return ret;
}