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
struct mlx4_ib_qp {int state; int /*<<< orphan*/  port; } ;
struct ib_wq {int /*<<< orphan*/  wq_num; } ;
struct ib_udata {int dummy; } ;
struct ib_qp_attr {int /*<<< orphan*/  port_num; } ;
struct ib_qp {int dummy; } ;
typedef  enum ib_wq_state { ____Placeholder_ib_wq_state } ib_wq_state ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;

/* Variables and functions */
 int IB_QPS_INIT ; 
 int IB_QPS_RESET ; 
 int IB_QP_PORT ; 
 int IB_WQS_RDY ; 
 int /*<<< orphan*/  MLX4_IB_RWQ_SRC ; 
 int __mlx4_ib_modify_qp (struct ib_wq*,int /*<<< orphan*/ ,struct ib_qp_attr*,int,int,int,struct ib_udata*) ; 
 int ib_wq2qp_state (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 struct mlx4_ib_qp* to_mqp (struct ib_qp*) ; 

__attribute__((used)) static int _mlx4_ib_modify_wq(struct ib_wq *ibwq, enum ib_wq_state new_state,
			      struct ib_udata *udata)
{
	struct mlx4_ib_qp *qp = to_mqp((struct ib_qp *)ibwq);
	enum ib_qp_state qp_cur_state;
	enum ib_qp_state qp_new_state;
	int attr_mask;
	int err;

	/* ib_qp.state represents the WQ HW state while ib_wq.state represents
	 * the WQ logic state.
	 */
	qp_cur_state = qp->state;
	qp_new_state = ib_wq2qp_state(new_state);

	if (ib_wq2qp_state(new_state) == qp_cur_state)
		return 0;

	if (new_state == IB_WQS_RDY) {
		struct ib_qp_attr attr = {};

		attr.port_num = qp->port;
		attr_mask = IB_QP_PORT;

		err = __mlx4_ib_modify_qp(ibwq, MLX4_IB_RWQ_SRC, &attr,
					  attr_mask, IB_QPS_RESET, IB_QPS_INIT,
					  udata);
		if (err) {
			pr_debug("WQN=0x%06x failed to apply RST->INIT on the HW QP\n",
				 ibwq->wq_num);
			return err;
		}

		qp_cur_state = IB_QPS_INIT;
	}

	attr_mask = 0;
	err = __mlx4_ib_modify_qp(ibwq, MLX4_IB_RWQ_SRC, NULL, attr_mask,
				  qp_cur_state,  qp_new_state, udata);

	if (err && (qp_cur_state == IB_QPS_INIT)) {
		qp_new_state = IB_QPS_RESET;
		if (__mlx4_ib_modify_qp(ibwq, MLX4_IB_RWQ_SRC, NULL,
					attr_mask, IB_QPS_INIT, IB_QPS_RESET,
					udata)) {
			pr_warn("WQN=0x%06x failed with reverting HW's resources failure\n",
				ibwq->wq_num);
			qp_new_state = IB_QPS_INIT;
		}
	}

	qp->state = qp_new_state;

	return err;
}