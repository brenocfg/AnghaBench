#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct qla_hw_data {scalar_t__ max_req_queues; scalar_t__ max_rsp_queues; int /*<<< orphan*/  mqenable; } ;
struct qla2xxx_mq_chain {int type; void** qregs; void* count; void* chain_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  rsp_q_out; int /*<<< orphan*/  rsp_q_in; int /*<<< orphan*/  req_q_out; int /*<<< orphan*/  req_q_in; } ;
struct TYPE_5__ {TYPE_1__ isp25mq; } ;
typedef  TYPE_2__ device_reg_t ;

/* Variables and functions */
 int DUMP_CHAIN_MQ ; 
 TYPE_2__* ISP_QUE_REG (struct qla_hw_data*,int) ; 
 scalar_t__ IS_QLA27XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA28XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA83XX (struct qla_hw_data*) ; 
 int RD_REG_DWORD (int /*<<< orphan*/ *) ; 
 void* htonl (int) ; 

__attribute__((used)) static inline void *
qla25xx_copy_mq(struct qla_hw_data *ha, void *ptr, uint32_t **last_chain)
{
	uint32_t cnt, que_idx;
	uint8_t que_cnt;
	struct qla2xxx_mq_chain *mq = ptr;
	device_reg_t *reg;

	if (!ha->mqenable || IS_QLA83XX(ha) || IS_QLA27XX(ha) ||
	    IS_QLA28XX(ha))
		return ptr;

	mq = ptr;
	*last_chain = &mq->type;
	mq->type = htonl(DUMP_CHAIN_MQ);
	mq->chain_size = htonl(sizeof(struct qla2xxx_mq_chain));

	que_cnt = ha->max_req_queues > ha->max_rsp_queues ?
		ha->max_req_queues : ha->max_rsp_queues;
	mq->count = htonl(que_cnt);
	for (cnt = 0; cnt < que_cnt; cnt++) {
		reg = ISP_QUE_REG(ha, cnt);
		que_idx = cnt * 4;
		mq->qregs[que_idx] =
		    htonl(RD_REG_DWORD(&reg->isp25mq.req_q_in));
		mq->qregs[que_idx+1] =
		    htonl(RD_REG_DWORD(&reg->isp25mq.req_q_out));
		mq->qregs[que_idx+2] =
		    htonl(RD_REG_DWORD(&reg->isp25mq.rsp_q_in));
		mq->qregs[que_idx+3] =
		    htonl(RD_REG_DWORD(&reg->isp25mq.rsp_q_out));
	}

	return ptr + sizeof(struct qla2xxx_mq_chain);
}