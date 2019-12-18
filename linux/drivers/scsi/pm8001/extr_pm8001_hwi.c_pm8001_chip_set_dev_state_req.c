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
struct set_dev_state_req {void* nds; void* device_id; void* tag; } ;
struct pm8001_hba_info {struct inbound_queue_table* inbnd_q_tbl; struct pm8001_ccb_info* ccb_info; } ;
struct pm8001_device {size_t device_id; } ;
struct pm8001_ccb_info {size_t ccb_tag; struct pm8001_device* device; } ;
struct inbound_queue_table {int dummy; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 size_t OPC_INB_SET_DEVICE_STATE ; 
 void* cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  memset (struct set_dev_state_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,size_t,struct set_dev_state_req*,int /*<<< orphan*/ ) ; 
 int pm8001_tag_alloc (struct pm8001_hba_info*,size_t*) ; 

int
pm8001_chip_set_dev_state_req(struct pm8001_hba_info *pm8001_ha,
	struct pm8001_device *pm8001_dev, u32 state)
{
	struct set_dev_state_req payload;
	struct inbound_queue_table *circularQ;
	struct pm8001_ccb_info *ccb;
	int rc;
	u32 tag;
	u32 opc = OPC_INB_SET_DEVICE_STATE;
	memset(&payload, 0, sizeof(payload));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	if (rc)
		return -1;
	ccb = &pm8001_ha->ccb_info[tag];
	ccb->ccb_tag = tag;
	ccb->device = pm8001_dev;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(tag);
	payload.device_id = cpu_to_le32(pm8001_dev->device_id);
	payload.nds = cpu_to_le32(state);
	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload, 0);
	return rc;

}