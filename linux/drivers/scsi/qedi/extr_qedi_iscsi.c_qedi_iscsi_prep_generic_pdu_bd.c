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
typedef  int u64 ;
typedef  void* u32 ;
struct TYPE_3__ {void* lo; void* hi; } ;
struct scsi_sge {scalar_t__ sge_len; TYPE_1__ sge_addr; } ;
struct TYPE_4__ {scalar_t__ resp_dma_addr; scalar_t__ resp_bd_tbl; scalar_t__ req_buf; scalar_t__ req_wr_ptr; scalar_t__ req_dma_addr; scalar_t__ req_bd_tbl; } ;
struct qedi_conn {TYPE_2__ gen_pdu; } ;

/* Variables and functions */
 scalar_t__ ISCSI_DEF_MAX_RECV_SEG_LEN ; 

__attribute__((used)) static void qedi_iscsi_prep_generic_pdu_bd(struct qedi_conn *qedi_conn)
{
	struct scsi_sge *bd_tbl;

	bd_tbl = (struct scsi_sge *)qedi_conn->gen_pdu.req_bd_tbl;

	bd_tbl->sge_addr.hi =
		(u32)((u64)qedi_conn->gen_pdu.req_dma_addr >> 32);
	bd_tbl->sge_addr.lo = (u32)qedi_conn->gen_pdu.req_dma_addr;
	bd_tbl->sge_len = qedi_conn->gen_pdu.req_wr_ptr -
				qedi_conn->gen_pdu.req_buf;
	bd_tbl = (struct scsi_sge  *)qedi_conn->gen_pdu.resp_bd_tbl;
	bd_tbl->sge_addr.hi =
			(u32)((u64)qedi_conn->gen_pdu.resp_dma_addr >> 32);
	bd_tbl->sge_addr.lo = (u32)qedi_conn->gen_pdu.resp_dma_addr;
	bd_tbl->sge_len = ISCSI_DEF_MAX_RECV_SEG_LEN;
}