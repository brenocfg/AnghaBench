#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_5__ {int qp_state; } ;
struct rxe_qp {int /*<<< orphan*/  srq; TYPE_2__ req; TYPE_1__ attr; } ;
struct TYPE_7__ {int max_mtu; } ;
struct rxe_port {TYPE_3__ attr; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_qp_rd_atom; } ;
struct rxe_dev {TYPE_4__ attr; struct rxe_port port; int /*<<< orphan*/  ib_dev; } ;
struct ib_qp_attr {int cur_qp_state; int qp_state; int port_num; int alt_port_num; int alt_timeout; int path_mtu; int timeout; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  alt_ah_attr; int /*<<< orphan*/  ah_attr; int /*<<< orphan*/  cap; } ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;
typedef  enum ib_mtu { ____Placeholder_ib_mtu } ib_mtu ;

/* Variables and functions */
 int EINVAL ; 
 int IB_QPS_ERR ; 
 int IB_QPS_SQD ; 
 int IB_QP_ALT_PATH ; 
 int IB_QP_AV ; 
 int IB_QP_CAP ; 
 int IB_QP_CUR_STATE ; 
 int IB_QP_MAX_QP_RD_ATOMIC ; 
 int IB_QP_PATH_MTU ; 
 int IB_QP_PORT ; 
 int IB_QP_STATE ; 
 int IB_QP_TIMEOUT ; 
 scalar_t__ QP_STATE_DRAIN ; 
 int /*<<< orphan*/  ib_modify_qp_is_ok (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ib_mtu_enum_to_int (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  qp_type (struct rxe_qp*) ; 
 int /*<<< orphan*/  rdma_is_port_valid (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rxe_av_chk_attr (struct rxe_dev*,int /*<<< orphan*/ *) ; 
 scalar_t__ rxe_qp_chk_cap (struct rxe_dev*,int /*<<< orphan*/ *,int) ; 

int rxe_qp_chk_attr(struct rxe_dev *rxe, struct rxe_qp *qp,
		    struct ib_qp_attr *attr, int mask)
{
	enum ib_qp_state cur_state = (mask & IB_QP_CUR_STATE) ?
					attr->cur_qp_state : qp->attr.qp_state;
	enum ib_qp_state new_state = (mask & IB_QP_STATE) ?
					attr->qp_state : cur_state;

	if (!ib_modify_qp_is_ok(cur_state, new_state, qp_type(qp), mask)) {
		pr_warn("invalid mask or state for qp\n");
		goto err1;
	}

	if (mask & IB_QP_STATE) {
		if (cur_state == IB_QPS_SQD) {
			if (qp->req.state == QP_STATE_DRAIN &&
			    new_state != IB_QPS_ERR)
				goto err1;
		}
	}

	if (mask & IB_QP_PORT) {
		if (!rdma_is_port_valid(&rxe->ib_dev, attr->port_num)) {
			pr_warn("invalid port %d\n", attr->port_num);
			goto err1;
		}
	}

	if (mask & IB_QP_CAP && rxe_qp_chk_cap(rxe, &attr->cap, !!qp->srq))
		goto err1;

	if (mask & IB_QP_AV && rxe_av_chk_attr(rxe, &attr->ah_attr))
		goto err1;

	if (mask & IB_QP_ALT_PATH) {
		if (rxe_av_chk_attr(rxe, &attr->alt_ah_attr))
			goto err1;
		if (!rdma_is_port_valid(&rxe->ib_dev, attr->alt_port_num))  {
			pr_warn("invalid alt port %d\n", attr->alt_port_num);
			goto err1;
		}
		if (attr->alt_timeout > 31) {
			pr_warn("invalid QP alt timeout %d > 31\n",
				attr->alt_timeout);
			goto err1;
		}
	}

	if (mask & IB_QP_PATH_MTU) {
		struct rxe_port *port = &rxe->port;

		enum ib_mtu max_mtu = port->attr.max_mtu;
		enum ib_mtu mtu = attr->path_mtu;

		if (mtu > max_mtu) {
			pr_debug("invalid mtu (%d) > (%d)\n",
				 ib_mtu_enum_to_int(mtu),
				 ib_mtu_enum_to_int(max_mtu));
			goto err1;
		}
	}

	if (mask & IB_QP_MAX_QP_RD_ATOMIC) {
		if (attr->max_rd_atomic > rxe->attr.max_qp_rd_atom) {
			pr_warn("invalid max_rd_atomic %d > %d\n",
				attr->max_rd_atomic,
				rxe->attr.max_qp_rd_atom);
			goto err1;
		}
	}

	if (mask & IB_QP_TIMEOUT) {
		if (attr->timeout > 31) {
			pr_warn("invalid QP timeout %d > 31\n",
				attr->timeout);
			goto err1;
		}
	}

	return 0;

err1:
	return -EINVAL;
}