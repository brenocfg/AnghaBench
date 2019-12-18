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
typedef  scalar_t__ uint32_t ;
typedef  size_t uint16_t ;
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
struct rsp_que {int dummy; } ;
struct req_que {scalar_t__ num_outstanding_cmds; int /*<<< orphan*/ ** outstanding_cmds; } ;
struct qla_hw_data {struct req_que** req_q_map; } ;
struct multi_sts_entry_fx00 {scalar_t__ handle_count; int /*<<< orphan*/ * handles; } ;
typedef  int /*<<< orphan*/  srb_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 scalar_t__ LSW (scalar_t__) ; 
 scalar_t__ MAX_HANDLE_COUNT ; 
 size_t MSW (scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg_io ; 
 int /*<<< orphan*/  qla2x00_process_completed_request (struct scsi_qla_host*,struct req_que*,scalar_t__) ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlafx00_multistatus_entry(struct scsi_qla_host *vha,
	struct rsp_que *rsp, void *pkt)
{
	srb_t		*sp;
	struct multi_sts_entry_fx00 *stsmfx;
	struct qla_hw_data *ha = vha->hw;
	uint32_t handle, hindex, handle_count, i;
	uint16_t que;
	struct req_que *req;
	__le32 *handle_ptr;

	stsmfx = (struct multi_sts_entry_fx00 *) pkt;

	handle_count = stsmfx->handle_count;

	if (handle_count > MAX_HANDLE_COUNT) {
		ql_dbg(ql_dbg_io, vha, 0x3035,
		    "Invalid handle count (0x%x).\n", handle_count);
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);
		return;
	}

	handle_ptr =  &stsmfx->handles[0];

	for (i = 0; i < handle_count; i++) {
		hindex = le32_to_cpu(*handle_ptr);
		handle = LSW(hindex);
		que = MSW(hindex);
		req = ha->req_q_map[que];

		/* Validate handle. */
		if (handle < req->num_outstanding_cmds)
			sp = req->outstanding_cmds[handle];
		else
			sp = NULL;

		if (sp == NULL) {
			ql_dbg(ql_dbg_io, vha, 0x3044,
			    "Invalid status handle (0x%x).\n", handle);
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
			return;
		}
		qla2x00_process_completed_request(vha, req, handle);
		handle_ptr++;
	}
}