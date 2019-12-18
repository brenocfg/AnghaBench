#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct mlx4_update_qp_params {int smac_index; } ;
struct TYPE_6__ {scalar_t__ smac; int smac_port; int smac_index; } ;
struct TYPE_5__ {int /*<<< orphan*/  qpn; } ;
struct mlx4_ib_qp {int /*<<< orphan*/  mutex; TYPE_3__ pri; TYPE_2__ mqp; } ;
struct TYPE_4__ {int /*<<< orphan*/ * mac; } ;
struct mlx4_ib_dev {int /*<<< orphan*/ * qp1_proxy_lock; int /*<<< orphan*/  dev; struct mlx4_ib_qp** qp1_proxy; TYPE_1__ iboe; } ;

/* Variables and functions */
 scalar_t__ MLX4_IB_INVALID_MAC ; 
 int /*<<< orphan*/  MLX4_UPDATE_QP_SMAC ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dev_base_lock ; 
 int /*<<< orphan*/  mlx4_is_mfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_mac_to_u64 (int /*<<< orphan*/ ) ; 
 int mlx4_register_mac (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  mlx4_unregister_mac (int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ mlx4_update_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx4_update_qp_params*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx4_ib_update_qps(struct mlx4_ib_dev *ibdev,
			       struct net_device *dev,
			       int port)
{
	u64 new_smac = 0;
	u64 release_mac = MLX4_IB_INVALID_MAC;
	struct mlx4_ib_qp *qp;

	read_lock(&dev_base_lock);
	new_smac = mlx4_mac_to_u64(dev->dev_addr);
	read_unlock(&dev_base_lock);

	atomic64_set(&ibdev->iboe.mac[port - 1], new_smac);

	/* no need for update QP1 and mac registration in non-SRIOV */
	if (!mlx4_is_mfunc(ibdev->dev))
		return;

	mutex_lock(&ibdev->qp1_proxy_lock[port - 1]);
	qp = ibdev->qp1_proxy[port - 1];
	if (qp) {
		int new_smac_index;
		u64 old_smac;
		struct mlx4_update_qp_params update_params;

		mutex_lock(&qp->mutex);
		old_smac = qp->pri.smac;
		if (new_smac == old_smac)
			goto unlock;

		new_smac_index = mlx4_register_mac(ibdev->dev, port, new_smac);

		if (new_smac_index < 0)
			goto unlock;

		update_params.smac_index = new_smac_index;
		if (mlx4_update_qp(ibdev->dev, qp->mqp.qpn, MLX4_UPDATE_QP_SMAC,
				   &update_params)) {
			release_mac = new_smac;
			goto unlock;
		}
		/* if old port was zero, no mac was yet registered for this QP */
		if (qp->pri.smac_port)
			release_mac = old_smac;
		qp->pri.smac = new_smac;
		qp->pri.smac_port = port;
		qp->pri.smac_index = new_smac_index;
	}

unlock:
	if (release_mac != MLX4_IB_INVALID_MAC)
		mlx4_unregister_mac(ibdev->dev, port, release_mac);
	if (qp)
		mutex_unlock(&qp->mutex);
	mutex_unlock(&ibdev->qp1_proxy_lock[port - 1]);
}