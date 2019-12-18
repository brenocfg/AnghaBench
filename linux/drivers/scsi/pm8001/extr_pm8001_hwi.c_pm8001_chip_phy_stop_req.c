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
typedef  int u32 ;
struct pm8001_hba_info {struct inbound_queue_table* inbnd_q_tbl; } ;
struct phy_stop_req {void* phy_id; void* tag; } ;
struct inbound_queue_table {int dummy; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int OPC_INB_PHYSTOP ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (struct phy_stop_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,int,struct phy_stop_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm8001_chip_phy_stop_req(struct pm8001_hba_info *pm8001_ha,
				    u8 phy_id)
{
	struct phy_stop_req payload;
	struct inbound_queue_table *circularQ;
	int ret;
	u32 tag = 0x01;
	u32 opcode = OPC_INB_PHYSTOP;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	memset(&payload, 0, sizeof(payload));
	payload.tag = cpu_to_le32(tag);
	payload.phy_id = cpu_to_le32(phy_id);
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opcode, &payload, 0);
	return ret;
}