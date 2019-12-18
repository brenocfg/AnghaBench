#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct reg_dev_req {int /*<<< orphan*/  sas_addr; void* firstburstsize_ITNexustimeout; void* dtype_dlr_mcn_ir_retry; void* phyid_portid; void* tag; } ;
struct pm8001_hba_info {struct pm8001_ccb_info* ccb_info; struct inbound_queue_table* inbnd_q_tbl; } ;
struct pm8001_device {scalar_t__ dev_type; int attached_phy; struct domain_device* sas_device; } ;
struct pm8001_ccb_info {int ccb_tag; struct pm8001_device* device; } ;
struct inbound_queue_table {int dummy; } ;
struct TYPE_5__ {TYPE_1__* ex_phy; } ;
struct domain_device {scalar_t__ linkrate; int /*<<< orphan*/  sas_addr; TYPE_3__* port; TYPE_2__ ex_dev; int /*<<< orphan*/  dev_type; struct domain_device* parent; } ;
typedef  int /*<<< orphan*/  payload ;
struct TYPE_6__ {scalar_t__ linkrate; int id; } ;
struct TYPE_4__ {int phy_id; } ;

/* Variables and functions */
 int OPC_INB_REG_DEV ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 scalar_t__ SAS_EDGE_EXPANDER_DEVICE ; 
 scalar_t__ SAS_END_DEVICE ; 
 scalar_t__ SAS_FANOUT_EXPANDER_DEVICE ; 
 scalar_t__ SAS_SATA_DEV ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ dev_is_expander (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct reg_dev_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,int,struct reg_dev_req*,int /*<<< orphan*/ ) ; 
 int pm8001_tag_alloc (struct pm8001_hba_info*,int*) ; 
 int /*<<< orphan*/  pm8001_tag_free (struct pm8001_hba_info*,int) ; 

__attribute__((used)) static int pm80xx_chip_reg_dev_req(struct pm8001_hba_info *pm8001_ha,
	struct pm8001_device *pm8001_dev, u32 flag)
{
	struct reg_dev_req payload;
	u32	opc;
	u32 stp_sspsmp_sata = 0x4;
	struct inbound_queue_table *circularQ;
	u32 linkrate, phy_id;
	int rc, tag = 0xdeadbeef;
	struct pm8001_ccb_info *ccb;
	u8 retryFlag = 0x1;
	u16 firstBurstSize = 0;
	u16 ITNT = 2000;
	struct domain_device *dev = pm8001_dev->sas_device;
	struct domain_device *parent_dev = dev->parent;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];

	memset(&payload, 0, sizeof(payload));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	if (rc)
		return rc;
	ccb = &pm8001_ha->ccb_info[tag];
	ccb->device = pm8001_dev;
	ccb->ccb_tag = tag;
	payload.tag = cpu_to_le32(tag);

	if (flag == 1) {
		stp_sspsmp_sata = 0x02; /*direct attached sata */
	} else {
		if (pm8001_dev->dev_type == SAS_SATA_DEV)
			stp_sspsmp_sata = 0x00; /* stp*/
		else if (pm8001_dev->dev_type == SAS_END_DEVICE ||
			pm8001_dev->dev_type == SAS_EDGE_EXPANDER_DEVICE ||
			pm8001_dev->dev_type == SAS_FANOUT_EXPANDER_DEVICE)
			stp_sspsmp_sata = 0x01; /*ssp or smp*/
	}
	if (parent_dev && dev_is_expander(parent_dev->dev_type))
		phy_id = parent_dev->ex_dev.ex_phy->phy_id;
	else
		phy_id = pm8001_dev->attached_phy;

	opc = OPC_INB_REG_DEV;

	linkrate = (pm8001_dev->sas_device->linkrate < dev->port->linkrate) ?
			pm8001_dev->sas_device->linkrate : dev->port->linkrate;

	payload.phyid_portid =
		cpu_to_le32(((pm8001_dev->sas_device->port->id) & 0xFF) |
		((phy_id & 0xFF) << 8));

	payload.dtype_dlr_mcn_ir_retry = cpu_to_le32((retryFlag & 0x01) |
		((linkrate & 0x0F) << 24) |
		((stp_sspsmp_sata & 0x03) << 28));
	payload.firstburstsize_ITNexustimeout =
		cpu_to_le32(ITNT | (firstBurstSize * 0x10000));

	memcpy(payload.sas_addr, pm8001_dev->sas_device->sas_addr,
		SAS_ADDR_SIZE);

	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload, 0);
	if (rc)
		pm8001_tag_free(pm8001_ha, tag);

	return rc;
}