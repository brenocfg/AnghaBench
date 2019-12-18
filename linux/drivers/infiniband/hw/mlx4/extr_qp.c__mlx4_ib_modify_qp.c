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
struct mlx4_ib_qp {int state; int port; int /*<<< orphan*/  mutex; } ;
struct mlx4_ib_dev {scalar_t__ num_ports; TYPE_2__* dev; int /*<<< orphan*/  ib_dev; } ;
struct ib_udata {int dummy; } ;
struct ib_qp_attr {int cur_qp_state; int qp_state; scalar_t__ port_num; scalar_t__ pkey_index; scalar_t__ max_rd_atomic; scalar_t__ max_dest_rd_atomic; } ;
struct ib_qp {int qp_type; scalar_t__ rwq_ind_tbl; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  device; } ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;
struct TYPE_3__ {scalar_t__* pkey_table_len; scalar_t__ max_qp_init_rdma; scalar_t__ max_qp_dest_rdma; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IB_LINK_LAYER_ETHERNET ; 
 int IB_QPS_INIT ; 
 int IB_QPS_RESET ; 
 int IB_QPS_RTR ; 
 int IB_QPT_RAW_PACKET ; 
 int IB_QPT_RC ; 
 int IB_QPT_UC ; 
 int IB_QPT_UD ; 
 int IB_QPT_XRC_INI ; 
 int IB_QP_CUR_STATE ; 
 int IB_QP_MAX_DEST_RD_ATOMIC ; 
 int IB_QP_MAX_QP_RD_ATOMIC ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_PORT ; 
 int IB_QP_STATE ; 
 int MLX4_IB_MODIFY_QP_RSS_SUP_ATTR_MSK ; 
 int /*<<< orphan*/  MLX4_IB_QP_SRC ; 
 int __mlx4_ib_modify_qp (struct ib_qp*,int /*<<< orphan*/ ,struct ib_qp_attr*,int,int,int,struct ib_udata*) ; 
 int /*<<< orphan*/  bring_down_rss_rwqs (scalar_t__,struct ib_udata*) ; 
 int bringup_rss_rwqs (scalar_t__,int,struct ib_udata*) ; 
 int /*<<< orphan*/  ib_modify_qp_is_ok (int,int,int,int) ; 
 scalar_t__ mlx4_ib_bond_next_port (struct mlx4_ib_dev*) ; 
 scalar_t__ mlx4_is_bonded (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int,...) ; 
 scalar_t__ rdma_port_get_link_layer (int /*<<< orphan*/ *,int) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_qp* to_mqp (struct ib_qp*) ; 

__attribute__((used)) static int _mlx4_ib_modify_qp(struct ib_qp *ibqp, struct ib_qp_attr *attr,
			      int attr_mask, struct ib_udata *udata)
{
	struct mlx4_ib_dev *dev = to_mdev(ibqp->device);
	struct mlx4_ib_qp *qp = to_mqp(ibqp);
	enum ib_qp_state cur_state, new_state;
	int err = -EINVAL;
	mutex_lock(&qp->mutex);

	cur_state = attr_mask & IB_QP_CUR_STATE ? attr->cur_qp_state : qp->state;
	new_state = attr_mask & IB_QP_STATE ? attr->qp_state : cur_state;

	if (!ib_modify_qp_is_ok(cur_state, new_state, ibqp->qp_type,
				attr_mask)) {
		pr_debug("qpn 0x%x: invalid attribute mask specified "
			 "for transition %d to %d. qp_type %d,"
			 " attr_mask 0x%x\n",
			 ibqp->qp_num, cur_state, new_state,
			 ibqp->qp_type, attr_mask);
		goto out;
	}

	if (ibqp->rwq_ind_tbl) {
		if (!(((cur_state == IB_QPS_RESET) &&
		       (new_state == IB_QPS_INIT)) ||
		      ((cur_state == IB_QPS_INIT)  &&
		       (new_state == IB_QPS_RTR)))) {
			pr_debug("qpn 0x%x: RSS QP unsupported transition %d to %d\n",
				 ibqp->qp_num, cur_state, new_state);

			err = -EOPNOTSUPP;
			goto out;
		}

		if (attr_mask & ~MLX4_IB_MODIFY_QP_RSS_SUP_ATTR_MSK) {
			pr_debug("qpn 0x%x: RSS QP unsupported attribute mask 0x%x for transition %d to %d\n",
				 ibqp->qp_num, attr_mask, cur_state, new_state);

			err = -EOPNOTSUPP;
			goto out;
		}
	}

	if (mlx4_is_bonded(dev->dev) && (attr_mask & IB_QP_PORT)) {
		if ((cur_state == IB_QPS_RESET) && (new_state == IB_QPS_INIT)) {
			if ((ibqp->qp_type == IB_QPT_RC) ||
			    (ibqp->qp_type == IB_QPT_UD) ||
			    (ibqp->qp_type == IB_QPT_UC) ||
			    (ibqp->qp_type == IB_QPT_RAW_PACKET) ||
			    (ibqp->qp_type == IB_QPT_XRC_INI)) {
				attr->port_num = mlx4_ib_bond_next_port(dev);
			}
		} else {
			/* no sense in changing port_num
			 * when ports are bonded */
			attr_mask &= ~IB_QP_PORT;
		}
	}

	if ((attr_mask & IB_QP_PORT) &&
	    (attr->port_num == 0 || attr->port_num > dev->num_ports)) {
		pr_debug("qpn 0x%x: invalid port number (%d) specified "
			 "for transition %d to %d. qp_type %d\n",
			 ibqp->qp_num, attr->port_num, cur_state,
			 new_state, ibqp->qp_type);
		goto out;
	}

	if ((attr_mask & IB_QP_PORT) && (ibqp->qp_type == IB_QPT_RAW_PACKET) &&
	    (rdma_port_get_link_layer(&dev->ib_dev, attr->port_num) !=
	     IB_LINK_LAYER_ETHERNET))
		goto out;

	if (attr_mask & IB_QP_PKEY_INDEX) {
		int p = attr_mask & IB_QP_PORT ? attr->port_num : qp->port;
		if (attr->pkey_index >= dev->dev->caps.pkey_table_len[p]) {
			pr_debug("qpn 0x%x: invalid pkey index (%d) specified "
				 "for transition %d to %d. qp_type %d\n",
				 ibqp->qp_num, attr->pkey_index, cur_state,
				 new_state, ibqp->qp_type);
			goto out;
		}
	}

	if (attr_mask & IB_QP_MAX_QP_RD_ATOMIC &&
	    attr->max_rd_atomic > dev->dev->caps.max_qp_init_rdma) {
		pr_debug("qpn 0x%x: max_rd_atomic (%d) too large. "
			 "Transition %d to %d. qp_type %d\n",
			 ibqp->qp_num, attr->max_rd_atomic, cur_state,
			 new_state, ibqp->qp_type);
		goto out;
	}

	if (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC &&
	    attr->max_dest_rd_atomic > dev->dev->caps.max_qp_dest_rdma) {
		pr_debug("qpn 0x%x: max_dest_rd_atomic (%d) too large. "
			 "Transition %d to %d. qp_type %d\n",
			 ibqp->qp_num, attr->max_dest_rd_atomic, cur_state,
			 new_state, ibqp->qp_type);
		goto out;
	}

	if (cur_state == new_state && cur_state == IB_QPS_RESET) {
		err = 0;
		goto out;
	}

	if (ibqp->rwq_ind_tbl && (new_state == IB_QPS_INIT)) {
		err = bringup_rss_rwqs(ibqp->rwq_ind_tbl, attr->port_num,
				       udata);
		if (err)
			goto out;
	}

	err = __mlx4_ib_modify_qp(ibqp, MLX4_IB_QP_SRC, attr, attr_mask,
				  cur_state, new_state, udata);

	if (ibqp->rwq_ind_tbl && err)
		bring_down_rss_rwqs(ibqp->rwq_ind_tbl, udata);

	if (mlx4_is_bonded(dev->dev) && (attr_mask & IB_QP_PORT))
		attr->port_num = 1;

out:
	mutex_unlock(&qp->mutex);
	return err;
}