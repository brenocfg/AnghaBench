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
struct rsp_que {int dummy; } ;
typedef  struct rsp_que req_que ;
struct qla_hw_data {int max_req_queues; int max_rsp_queues; struct rsp_que** rsp_q_map; int /*<<< orphan*/  hardware_lock; int /*<<< orphan*/  rsp_qid_map; struct rsp_que** req_q_map; int /*<<< orphan*/  req_qid_map; struct rsp_que** base_qpair; struct rsp_que** queue_pair_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rsp_que**) ; 
 int /*<<< orphan*/  qla2x00_free_req_que (struct qla_hw_data*,struct rsp_que*) ; 
 int /*<<< orphan*/  qla2x00_free_rsp_que (struct qla_hw_data*,struct rsp_que*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qla2x00_free_queues(struct qla_hw_data *ha)
{
	struct req_que *req;
	struct rsp_que *rsp;
	int cnt;
	unsigned long flags;

	if (ha->queue_pair_map) {
		kfree(ha->queue_pair_map);
		ha->queue_pair_map = NULL;
	}
	if (ha->base_qpair) {
		kfree(ha->base_qpair);
		ha->base_qpair = NULL;
	}

	spin_lock_irqsave(&ha->hardware_lock, flags);
	for (cnt = 0; cnt < ha->max_req_queues; cnt++) {
		if (!test_bit(cnt, ha->req_qid_map))
			continue;

		req = ha->req_q_map[cnt];
		clear_bit(cnt, ha->req_qid_map);
		ha->req_q_map[cnt] = NULL;

		spin_unlock_irqrestore(&ha->hardware_lock, flags);
		qla2x00_free_req_que(ha, req);
		spin_lock_irqsave(&ha->hardware_lock, flags);
	}
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	kfree(ha->req_q_map);
	ha->req_q_map = NULL;


	spin_lock_irqsave(&ha->hardware_lock, flags);
	for (cnt = 0; cnt < ha->max_rsp_queues; cnt++) {
		if (!test_bit(cnt, ha->rsp_qid_map))
			continue;

		rsp = ha->rsp_q_map[cnt];
		clear_bit(cnt, ha->rsp_qid_map);
		ha->rsp_q_map[cnt] =  NULL;
		spin_unlock_irqrestore(&ha->hardware_lock, flags);
		qla2x00_free_rsp_que(ha, rsp);
		spin_lock_irqsave(&ha->hardware_lock, flags);
	}
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	kfree(ha->rsp_q_map);
	ha->rsp_q_map = NULL;
}