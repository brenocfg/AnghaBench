#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint16_t ;
struct TYPE_16__ {scalar_t__ n2n_bigger; } ;
struct qla_hw_data {int switch_cap; int /*<<< orphan*/  hardware_lock; TYPE_2__ flags; void* current_topology; void* operating_mode; int /*<<< orphan*/  min_external_loopid; int /*<<< orphan*/  loop_down_timer; int /*<<< orphan*/  pdev; } ;
struct TYPE_17__ {int /*<<< orphan*/  init_done; } ;
struct TYPE_18__ {int loop_id; TYPE_3__ flags; int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
struct TYPE_15__ {scalar_t__ rsvd_1; void* al_pa; void* area; void* domain; } ;
struct TYPE_19__ {TYPE_1__ b; } ;
typedef  TYPE_5__ port_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 void* ISP_CFG_F ; 
 void* ISP_CFG_FL ; 
 void* ISP_CFG_N ; 
 void* ISP_CFG_NL ; 
 scalar_t__ IS_CNA_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 void* LOOP ; 
 scalar_t__ LOOP_TRANSITION (TYPE_4__*) ; 
 void* P2P ; 
 int QLA_COMMAND_ERROR ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SNS_FIRST_LOOP_ID ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_4__* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_4__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_4__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla24xx_link_initialize (TYPE_4__*) ; 
 int qla2x00_get_adapter_id (TYPE_4__*,int*,void**,void**,void**,int*,int*) ; 
 int /*<<< orphan*/  qlt_update_host_map (TYPE_4__*,TYPE_5__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int
qla2x00_configure_hba(scsi_qla_host_t *vha)
{
	int       rval;
	uint16_t      loop_id;
	uint16_t      topo;
	uint16_t      sw_cap;
	uint8_t       al_pa;
	uint8_t       area;
	uint8_t       domain;
	char		connect_type[22];
	struct qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);
	port_id_t id;
	unsigned long flags;

	/* Get host addresses. */
	rval = qla2x00_get_adapter_id(vha,
	    &loop_id, &al_pa, &area, &domain, &topo, &sw_cap);
	if (rval != QLA_SUCCESS) {
		if (LOOP_TRANSITION(vha) || atomic_read(&ha->loop_down_timer) ||
		    IS_CNA_CAPABLE(ha) ||
		    (rval == QLA_COMMAND_ERROR && loop_id == 0x7)) {
			ql_dbg(ql_dbg_disc, vha, 0x2008,
			    "Loop is in a transition state.\n");
		} else {
			ql_log(ql_log_warn, vha, 0x2009,
			    "Unable to get host loop ID.\n");
			if (IS_FWI2_CAPABLE(ha) && (vha == base_vha) &&
			    (rval == QLA_COMMAND_ERROR && loop_id == 0x1b)) {
				ql_log(ql_log_warn, vha, 0x1151,
				    "Doing link init.\n");
				if (qla24xx_link_initialize(vha) == QLA_SUCCESS)
					return rval;
			}
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		}
		return (rval);
	}

	if (topo == 4) {
		ql_log(ql_log_info, vha, 0x200a,
		    "Cannot get topology - retrying.\n");
		return (QLA_FUNCTION_FAILED);
	}

	vha->loop_id = loop_id;

	/* initialize */
	ha->min_external_loopid = SNS_FIRST_LOOP_ID;
	ha->operating_mode = LOOP;
	ha->switch_cap = 0;

	switch (topo) {
	case 0:
		ql_dbg(ql_dbg_disc, vha, 0x200b, "HBA in NL topology.\n");
		ha->current_topology = ISP_CFG_NL;
		strcpy(connect_type, "(Loop)");
		break;

	case 1:
		ql_dbg(ql_dbg_disc, vha, 0x200c, "HBA in FL topology.\n");
		ha->switch_cap = sw_cap;
		ha->current_topology = ISP_CFG_FL;
		strcpy(connect_type, "(FL_Port)");
		break;

	case 2:
		ql_dbg(ql_dbg_disc, vha, 0x200d, "HBA in N P2P topology.\n");
		ha->operating_mode = P2P;
		ha->current_topology = ISP_CFG_N;
		strcpy(connect_type, "(N_Port-to-N_Port)");
		break;

	case 3:
		ql_dbg(ql_dbg_disc, vha, 0x200e, "HBA in F P2P topology.\n");
		ha->switch_cap = sw_cap;
		ha->operating_mode = P2P;
		ha->current_topology = ISP_CFG_F;
		strcpy(connect_type, "(F_Port)");
		break;

	default:
		ql_dbg(ql_dbg_disc, vha, 0x200f,
		    "HBA in unknown topology %x, using NL.\n", topo);
		ha->current_topology = ISP_CFG_NL;
		strcpy(connect_type, "(Loop)");
		break;
	}

	/* Save Host port and loop ID. */
	/* byte order - Big Endian */
	id.b.domain = domain;
	id.b.area = area;
	id.b.al_pa = al_pa;
	id.b.rsvd_1 = 0;
	spin_lock_irqsave(&ha->hardware_lock, flags);
	if (!(topo == 2 && ha->flags.n2n_bigger))
		qlt_update_host_map(vha, id);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	if (!vha->flags.init_done)
		ql_log(ql_log_info, vha, 0x2010,
		    "Topology - %s, Host Loop address 0x%x.\n",
		    connect_type, vha->loop_id);

	return(rval);
}