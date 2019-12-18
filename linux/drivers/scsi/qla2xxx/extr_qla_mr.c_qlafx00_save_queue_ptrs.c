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
typedef  int /*<<< orphan*/  u64 ;
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct rsp_que {scalar_t__ dma_fx00; int /*<<< orphan*/  length_fx00; int /*<<< orphan*/  ring_fx00; scalar_t__ dma; int /*<<< orphan*/  ring; int /*<<< orphan*/  length; } ;
struct req_que {scalar_t__ dma_fx00; int /*<<< orphan*/  length_fx00; int /*<<< orphan*/  ring_fx00; scalar_t__ dma; int /*<<< orphan*/  ring; int /*<<< orphan*/  length; } ;
struct qla_hw_data {struct rsp_que** rsp_q_map; struct rsp_que** req_q_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,struct rsp_que*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_init ; 

__attribute__((used)) static void
qlafx00_save_queue_ptrs(struct scsi_qla_host *vha)
{
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req = ha->req_q_map[0];
	struct rsp_que *rsp = ha->rsp_q_map[0];

	req->length_fx00 = req->length;
	req->ring_fx00 = req->ring;
	req->dma_fx00 = req->dma;

	rsp->length_fx00 = rsp->length;
	rsp->ring_fx00 = rsp->ring;
	rsp->dma_fx00 = rsp->dma;

	ql_dbg(ql_dbg_init, vha, 0x012d,
	    "req: %p, ring_fx00: %p, length_fx00: 0x%x,"
	    "req->dma_fx00: 0x%llx\n", req, req->ring_fx00,
	    req->length_fx00, (u64)req->dma_fx00);

	ql_dbg(ql_dbg_init, vha, 0x012e,
	    "rsp: %p, ring_fx00: %p, length_fx00: 0x%x,"
	    "rsp->dma_fx00: 0x%llx\n", rsp, rsp->ring_fx00,
	    rsp->length_fx00, (u64)rsp->dma_fx00);
}