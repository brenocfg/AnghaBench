#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int flags; int /*<<< orphan*/  vp_index; scalar_t__ srr_reject_code_expl; scalar_t__ srr_reject_code; scalar_t__ srr_flags; int /*<<< orphan*/  srr_ui; int /*<<< orphan*/  srr_rel_offs; int /*<<< orphan*/  exchange_address; int /*<<< orphan*/  fw_handle; int /*<<< orphan*/  status_subcode; int /*<<< orphan*/  status; int /*<<< orphan*/  srr_rx_id; int /*<<< orphan*/  nport_handle; int /*<<< orphan*/  handle; } ;
struct TYPE_16__ {TYPE_5__ isp24; } ;
struct nack_to_isp {int entry_count; TYPE_6__ u; int /*<<< orphan*/  ox_id; int /*<<< orphan*/  entry_type; } ;
struct TYPE_17__ {int flags; int /*<<< orphan*/  vp_index; int /*<<< orphan*/  srr_ui; int /*<<< orphan*/  srr_rel_offs; int /*<<< orphan*/  exchange_address; int /*<<< orphan*/  fw_handle; int /*<<< orphan*/  status_subcode; int /*<<< orphan*/  status; int /*<<< orphan*/  srr_rx_id; int /*<<< orphan*/  nport_handle; } ;
struct TYPE_18__ {TYPE_7__ isp24; } ;
struct imm_ntfy_from_isp {TYPE_8__ u; int /*<<< orphan*/  ox_id; } ;
struct TYPE_11__ {struct imm_ntfy_from_isp* ntfy; } ;
struct TYPE_12__ {TYPE_1__ nack; } ;
struct TYPE_13__ {TYPE_2__ u; } ;
struct TYPE_14__ {TYPE_3__ iocb_cmd; } ;
struct TYPE_19__ {int /*<<< orphan*/  handle; TYPE_4__ u; } ;
typedef  TYPE_9__ srb_t ;

/* Variables and functions */
 scalar_t__ IMM_NTFY_ELS ; 
 int /*<<< orphan*/  NOTIFY24XX_FLAGS_PUREX_IOCB ; 
 int /*<<< orphan*/  NOTIFY_ACK_TYPE ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qla2x00_send_notify_ack_iocb(srb_t *sp,
	struct nack_to_isp *nack)
{
	struct imm_ntfy_from_isp *ntfy = sp->u.iocb_cmd.u.nack.ntfy;

	nack->entry_type = NOTIFY_ACK_TYPE;
	nack->entry_count = 1;
	nack->ox_id = ntfy->ox_id;

	nack->u.isp24.handle = sp->handle;
	nack->u.isp24.nport_handle = ntfy->u.isp24.nport_handle;
	if (le16_to_cpu(ntfy->u.isp24.status) == IMM_NTFY_ELS) {
		nack->u.isp24.flags = ntfy->u.isp24.flags &
			cpu_to_le32(NOTIFY24XX_FLAGS_PUREX_IOCB);
	}
	nack->u.isp24.srr_rx_id = ntfy->u.isp24.srr_rx_id;
	nack->u.isp24.status = ntfy->u.isp24.status;
	nack->u.isp24.status_subcode = ntfy->u.isp24.status_subcode;
	nack->u.isp24.fw_handle = ntfy->u.isp24.fw_handle;
	nack->u.isp24.exchange_address = ntfy->u.isp24.exchange_address;
	nack->u.isp24.srr_rel_offs = ntfy->u.isp24.srr_rel_offs;
	nack->u.isp24.srr_ui = ntfy->u.isp24.srr_ui;
	nack->u.isp24.srr_flags = 0;
	nack->u.isp24.srr_reject_code = 0;
	nack->u.isp24.srr_reject_code_expl = 0;
	nack->u.isp24.vp_index = ntfy->u.isp24.vp_index;
}