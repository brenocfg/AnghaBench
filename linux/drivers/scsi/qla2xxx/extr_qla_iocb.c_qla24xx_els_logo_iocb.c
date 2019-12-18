#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_26__ {scalar_t__ els_cmd; int /*<<< orphan*/  els_logo_pyld_dma; } ;
struct TYPE_25__ {int /*<<< orphan*/  els_resp_pyld_dma; int /*<<< orphan*/  els_plogi_pyld_dma; } ;
struct TYPE_27__ {TYPE_8__ els_logo; TYPE_7__ els_plogi; } ;
struct srb_iocb {TYPE_9__ u; } ;
struct els_plogi_payload {int dummy; } ;
struct els_logo_payload {int dummy; } ;
struct els_entry_24xx {int entry_count; int tx_dsd_count; int rx_dsd_count; scalar_t__ opcode; int control_flags; void* rx_len; int /*<<< orphan*/  rx_address; void* rx_byte_count; void* tx_len; int /*<<< orphan*/  tx_address; void* tx_byte_count; int /*<<< orphan*/ * s_id; int /*<<< orphan*/ * port_id; int /*<<< orphan*/  sof_type; int /*<<< orphan*/  vp_index; int /*<<< orphan*/  nport_handle; int /*<<< orphan*/  handle; scalar_t__ entry_status; scalar_t__ sys_define; int /*<<< orphan*/  entry_type; } ;
struct TYPE_19__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_17__ {TYPE_12__* vha; TYPE_4__* fcport; int /*<<< orphan*/  handle; TYPE_1__ u; } ;
typedef  TYPE_11__ srb_t ;
struct TYPE_16__ {int /*<<< orphan*/  control_requests; } ;
struct TYPE_23__ {int /*<<< orphan*/  domain; int /*<<< orphan*/  area; int /*<<< orphan*/  al_pa; } ;
struct TYPE_24__ {TYPE_5__ b; } ;
struct TYPE_18__ {TYPE_10__ qla_stats; TYPE_6__ d_id; int /*<<< orphan*/  vp_idx; } ;
typedef  TYPE_12__ scsi_qla_host_t ;
struct TYPE_20__ {int /*<<< orphan*/  domain; int /*<<< orphan*/  area; int /*<<< orphan*/  al_pa; } ;
struct TYPE_21__ {TYPE_2__ b; } ;
struct TYPE_22__ {TYPE_3__ d_id; int /*<<< orphan*/  loop_id; } ;

/* Variables and functions */
 scalar_t__ ELS_DCMD_PLOGI ; 
 int /*<<< orphan*/  ELS_IOCB_TYPE ; 
 int /*<<< orphan*/  EST_SOFI3 ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  put_unaligned_le64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (scalar_t__,TYPE_12__*,int,char*) ; 
 scalar_t__ ql_dbg_buffer ; 
 scalar_t__ ql_dbg_io ; 
 int /*<<< orphan*/  ql_dump_buffer (int /*<<< orphan*/ ,TYPE_12__*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ql_log_info ; 

__attribute__((used)) static void
qla24xx_els_logo_iocb(srb_t *sp, struct els_entry_24xx *els_iocb)
{
	scsi_qla_host_t *vha = sp->vha;
	struct srb_iocb *elsio = &sp->u.iocb_cmd;

	els_iocb->entry_type = ELS_IOCB_TYPE;
	els_iocb->entry_count = 1;
	els_iocb->sys_define = 0;
	els_iocb->entry_status = 0;
	els_iocb->handle = sp->handle;
	els_iocb->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	els_iocb->tx_dsd_count = 1;
	els_iocb->vp_index = vha->vp_idx;
	els_iocb->sof_type = EST_SOFI3;
	els_iocb->rx_dsd_count = 0;
	els_iocb->opcode = elsio->u.els_logo.els_cmd;

	els_iocb->port_id[0] = sp->fcport->d_id.b.al_pa;
	els_iocb->port_id[1] = sp->fcport->d_id.b.area;
	els_iocb->port_id[2] = sp->fcport->d_id.b.domain;
	/* For SID the byte order is different than DID */
	els_iocb->s_id[1] = vha->d_id.b.al_pa;
	els_iocb->s_id[2] = vha->d_id.b.area;
	els_iocb->s_id[0] = vha->d_id.b.domain;

	if (elsio->u.els_logo.els_cmd == ELS_DCMD_PLOGI) {
		els_iocb->control_flags = 0;
		els_iocb->tx_byte_count = els_iocb->tx_len =
			cpu_to_le32(sizeof(struct els_plogi_payload));
		put_unaligned_le64(elsio->u.els_plogi.els_plogi_pyld_dma,
				   &els_iocb->tx_address);
		els_iocb->rx_dsd_count = 1;
		els_iocb->rx_byte_count = els_iocb->rx_len =
			cpu_to_le32(sizeof(struct els_plogi_payload));
		put_unaligned_le64(elsio->u.els_plogi.els_resp_pyld_dma,
				   &els_iocb->rx_address);

		ql_dbg(ql_dbg_io + ql_dbg_buffer, vha, 0x3073,
		    "PLOGI ELS IOCB:\n");
		ql_dump_buffer(ql_log_info, vha, 0x0109,
		    (uint8_t *)els_iocb, 0x70);
	} else {
		els_iocb->control_flags = 1 << 13;
		els_iocb->tx_byte_count =
			cpu_to_le32(sizeof(struct els_logo_payload));
		put_unaligned_le64(elsio->u.els_logo.els_logo_pyld_dma,
				   &els_iocb->tx_address);
		els_iocb->tx_len = cpu_to_le32(sizeof(struct els_logo_payload));

		els_iocb->rx_byte_count = 0;
		els_iocb->rx_address = 0;
		els_iocb->rx_len = 0;
	}

	sp->vha->qla_stats.control_requests++;
}