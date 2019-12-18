#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mlx4_vport_state {scalar_t__ vlan_proto; scalar_t__ link_state; scalar_t__ qos_vport; int /*<<< orphan*/  default_qos; scalar_t__ default_vlan; } ;
struct TYPE_12__ {scalar_t__ vlan_proto; scalar_t__ link_state; scalar_t__ qos_vport; scalar_t__ default_vlan; int /*<<< orphan*/  default_qos; } ;
struct mlx4_vport_oper_state {int vlan_idx; TYPE_5__ state; } ;
struct mlx4_vf_immed_vlan_work {int flags; int orig_vlan_ix; int port; int slave; scalar_t__ qos_vport; int vlan_ix; scalar_t__ vlan_proto; int /*<<< orphan*/  work; struct mlx4_priv* priv; scalar_t__ vlan_id; int /*<<< orphan*/  qos; scalar_t__ orig_vlan_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  comm_wq; TYPE_3__* slave_state; TYPE_2__* vf_admin; TYPE_1__* vf_oper; } ;
struct TYPE_14__ {TYPE_6__ master; } ;
struct TYPE_11__ {int flags2; } ;
struct mlx4_dev {TYPE_4__ caps; } ;
struct mlx4_priv {TYPE_7__ mfunc; struct mlx4_dev dev; } ;
struct TYPE_10__ {scalar_t__ active; } ;
struct TYPE_9__ {struct mlx4_vport_state* vport; } ;
struct TYPE_8__ {struct mlx4_vport_oper_state* vport; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IFLA_VF_LINK_STATE_DISABLE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX4_DEV_CAP_FLAG2_UPDATE_QP ; 
 int MLX4_VF_IMMED_VLAN_FLAG_LINK_DISABLE ; 
 int MLX4_VF_IMMED_VLAN_FLAG_QOS ; 
 int MLX4_VF_IMMED_VLAN_FLAG_VLAN ; 
 scalar_t__ MLX4_VGT ; 
 int NO_INDX ; 
 int __mlx4_register_vlan (struct mlx4_dev*,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  kfree (struct mlx4_vf_immed_vlan_work*) ; 
 struct mlx4_vf_immed_vlan_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,int,int,...) ; 
 int /*<<< orphan*/  mlx4_vf_immed_vlan_work_handler ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx4_master_immediate_activate_vlan_qos(struct mlx4_priv *priv,
					    int slave, int port)
{
	struct mlx4_vport_oper_state *vp_oper;
	struct mlx4_vport_state *vp_admin;
	struct mlx4_vf_immed_vlan_work *work;
	struct mlx4_dev *dev = &(priv->dev);
	int err;
	int admin_vlan_ix = NO_INDX;

	vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
	vp_admin = &priv->mfunc.master.vf_admin[slave].vport[port];

	if (vp_oper->state.default_vlan == vp_admin->default_vlan &&
	    vp_oper->state.default_qos == vp_admin->default_qos &&
	    vp_oper->state.vlan_proto == vp_admin->vlan_proto &&
	    vp_oper->state.link_state == vp_admin->link_state &&
	    vp_oper->state.qos_vport == vp_admin->qos_vport)
		return 0;

	if (!(priv->mfunc.master.slave_state[slave].active &&
	      dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_UPDATE_QP)) {
		/* even if the UPDATE_QP command isn't supported, we still want
		 * to set this VF link according to the admin directive
		 */
		vp_oper->state.link_state = vp_admin->link_state;
		return -1;
	}

	mlx4_dbg(dev, "updating immediately admin params slave %d port %d\n",
		 slave, port);
	mlx4_dbg(dev, "vlan %d QoS %d link down %d\n",
		 vp_admin->default_vlan, vp_admin->default_qos,
		 vp_admin->link_state);

	work = kzalloc(sizeof(*work), GFP_KERNEL);
	if (!work)
		return -ENOMEM;

	if (vp_oper->state.default_vlan != vp_admin->default_vlan) {
		if (MLX4_VGT != vp_admin->default_vlan) {
			err = __mlx4_register_vlan(&priv->dev, port,
						   vp_admin->default_vlan,
						   &admin_vlan_ix);
			if (err) {
				kfree(work);
				mlx4_warn(&priv->dev,
					  "No vlan resources slave %d, port %d\n",
					  slave, port);
				return err;
			}
		} else {
			admin_vlan_ix = NO_INDX;
		}
		work->flags |= MLX4_VF_IMMED_VLAN_FLAG_VLAN;
		mlx4_dbg(&priv->dev,
			 "alloc vlan %d idx  %d slave %d port %d\n",
			 (int)(vp_admin->default_vlan),
			 admin_vlan_ix, slave, port);
	}

	/* save original vlan ix and vlan id */
	work->orig_vlan_id = vp_oper->state.default_vlan;
	work->orig_vlan_ix = vp_oper->vlan_idx;

	/* handle new qos */
	if (vp_oper->state.default_qos != vp_admin->default_qos)
		work->flags |= MLX4_VF_IMMED_VLAN_FLAG_QOS;

	if (work->flags & MLX4_VF_IMMED_VLAN_FLAG_VLAN)
		vp_oper->vlan_idx = admin_vlan_ix;

	vp_oper->state.default_vlan = vp_admin->default_vlan;
	vp_oper->state.default_qos = vp_admin->default_qos;
	vp_oper->state.vlan_proto = vp_admin->vlan_proto;
	vp_oper->state.link_state = vp_admin->link_state;
	vp_oper->state.qos_vport = vp_admin->qos_vport;

	if (vp_admin->link_state == IFLA_VF_LINK_STATE_DISABLE)
		work->flags |= MLX4_VF_IMMED_VLAN_FLAG_LINK_DISABLE;

	/* iterate over QPs owned by this slave, using UPDATE_QP */
	work->port = port;
	work->slave = slave;
	work->qos = vp_oper->state.default_qos;
	work->qos_vport = vp_oper->state.qos_vport;
	work->vlan_id = vp_oper->state.default_vlan;
	work->vlan_ix = vp_oper->vlan_idx;
	work->vlan_proto = vp_oper->state.vlan_proto;
	work->priv = priv;
	INIT_WORK(&work->work, mlx4_vf_immed_vlan_work_handler);
	queue_work(priv->mfunc.master.comm_wq, &work->work);

	return 0;
}