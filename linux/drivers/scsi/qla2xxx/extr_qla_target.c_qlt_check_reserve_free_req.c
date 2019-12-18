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
typedef  scalar_t__ uint16_t ;
struct req_que {scalar_t__ cnt; scalar_t__ ring_index; scalar_t__ length; int /*<<< orphan*/  req_q_out; scalar_t__* out_ptr; } ;
struct qla_qpair {scalar_t__ use_shadow_reg; struct req_que* req; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ RD_REG_DWORD_RELAXED (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int qlt_check_reserve_free_req(struct qla_qpair *qpair,
	uint32_t req_cnt)
{
	uint32_t cnt;
	struct req_que *req = qpair->req;

	if (req->cnt < (req_cnt + 2)) {
		cnt = (uint16_t)(qpair->use_shadow_reg ? *req->out_ptr :
		    RD_REG_DWORD_RELAXED(req->req_q_out));

		if  (req->ring_index < cnt)
			req->cnt = cnt - req->ring_index;
		else
			req->cnt = req->length - (req->ring_index - cnt);

		if (unlikely(req->cnt < (req_cnt + 2)))
			return -EAGAIN;
	}

	req->cnt -= req_cnt;

	return 0;
}