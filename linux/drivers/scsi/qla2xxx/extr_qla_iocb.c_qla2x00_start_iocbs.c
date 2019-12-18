#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct req_que {scalar_t__ ring_index; scalar_t__ length; int /*<<< orphan*/ * req_q_in; int /*<<< orphan*/  ring_ptr; int /*<<< orphan*/  ring; int /*<<< orphan*/  id; } ;
struct qla_hw_data {int /*<<< orphan*/  rqstq_intr_code; TYPE_2__* iobase; scalar_t__ mqenable; } ;
struct TYPE_10__ {int /*<<< orphan*/  req_q_in; } ;
struct TYPE_9__ {int /*<<< orphan*/  req_q_in; } ;
struct TYPE_11__ {int /*<<< orphan*/  isp; TYPE_4__ isp24; TYPE_3__ ispfx00; } ;
typedef  TYPE_5__ device_reg_t ;
struct TYPE_7__ {int /*<<< orphan*/  hccr; } ;
struct TYPE_8__ {TYPE_1__ isp24; } ;

/* Variables and functions */
 TYPE_5__* ISP_QUE_REG (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_REQ_Q_IN (struct qla_hw_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_P3P_TYPE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA27XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA28XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA83XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLAFX00 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  QLAFX00_SET_HST_INTR (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RD_REG_DWORD_RELAXED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RD_REG_WORD_RELAXED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRT_REG_DWORD (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WRT_REG_WORD (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qla82xx_start_iocbs (struct scsi_qla_host*) ; 

void
qla2x00_start_iocbs(struct scsi_qla_host *vha, struct req_que *req)
{
	struct qla_hw_data *ha = vha->hw;
	device_reg_t *reg = ISP_QUE_REG(ha, req->id);

	if (IS_P3P_TYPE(ha)) {
		qla82xx_start_iocbs(vha);
	} else {
		/* Adjust ring index. */
		req->ring_index++;
		if (req->ring_index == req->length) {
			req->ring_index = 0;
			req->ring_ptr = req->ring;
		} else
			req->ring_ptr++;

		/* Set chip new ring index. */
		if (ha->mqenable || IS_QLA27XX(ha) || IS_QLA28XX(ha)) {
			WRT_REG_DWORD(req->req_q_in, req->ring_index);
		} else if (IS_QLA83XX(ha)) {
			WRT_REG_DWORD(req->req_q_in, req->ring_index);
			RD_REG_DWORD_RELAXED(&ha->iobase->isp24.hccr);
		} else if (IS_QLAFX00(ha)) {
			WRT_REG_DWORD(&reg->ispfx00.req_q_in, req->ring_index);
			RD_REG_DWORD_RELAXED(&reg->ispfx00.req_q_in);
			QLAFX00_SET_HST_INTR(ha, ha->rqstq_intr_code);
		} else if (IS_FWI2_CAPABLE(ha)) {
			WRT_REG_DWORD(&reg->isp24.req_q_in, req->ring_index);
			RD_REG_DWORD_RELAXED(&reg->isp24.req_q_in);
		} else {
			WRT_REG_WORD(ISP_REQ_Q_IN(ha, &reg->isp),
				req->ring_index);
			RD_REG_WORD_RELAXED(ISP_REQ_Q_IN(ha, &reg->isp));
		}
	}
}