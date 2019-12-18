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
union ib_gid {int /*<<< orphan*/  raw; } ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx4_flow_reg_id {scalar_t__ mirror; scalar_t__ id; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct mlx4_ib_steering {int /*<<< orphan*/  list; struct mlx4_flow_reg_id reg_id; TYPE_2__ gid; } ;
struct mlx4_ib_qp {int port; int flags; int /*<<< orphan*/  mqp; int /*<<< orphan*/  mutex; int /*<<< orphan*/  steering_rules; } ;
struct mlx4_ib_dev {struct mlx4_dev* dev; } ;
struct TYPE_3__ {scalar_t__ steering_mode; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
typedef  enum mlx4_protocol { ____Placeholder_mlx4_protocol } mlx4_protocol ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK ; 
 int MLX4_PROT_IB_IPV6 ; 
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 int add_gid_entry (struct ib_qp*,union ib_gid*) ; 
 int /*<<< orphan*/  kfree (struct mlx4_ib_steering*) ; 
 struct mlx4_ib_steering* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mlx4_is_bonded (struct mlx4_dev*) ; 
 int mlx4_multicast_attach (struct mlx4_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  mlx4_multicast_detach (struct mlx4_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_qp* to_mqp (struct ib_qp*) ; 

__attribute__((used)) static int mlx4_ib_mcg_attach(struct ib_qp *ibqp, union ib_gid *gid, u16 lid)
{
	int err;
	struct mlx4_ib_dev *mdev = to_mdev(ibqp->device);
	struct mlx4_dev	*dev = mdev->dev;
	struct mlx4_ib_qp *mqp = to_mqp(ibqp);
	struct mlx4_ib_steering *ib_steering = NULL;
	enum mlx4_protocol prot = MLX4_PROT_IB_IPV6;
	struct mlx4_flow_reg_id	reg_id;

	if (mdev->dev->caps.steering_mode ==
	    MLX4_STEERING_MODE_DEVICE_MANAGED) {
		ib_steering = kmalloc(sizeof(*ib_steering), GFP_KERNEL);
		if (!ib_steering)
			return -ENOMEM;
	}

	err = mlx4_multicast_attach(mdev->dev, &mqp->mqp, gid->raw, mqp->port,
				    !!(mqp->flags &
				       MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK),
				    prot, &reg_id.id);
	if (err) {
		pr_err("multicast attach op failed, err %d\n", err);
		goto err_malloc;
	}

	reg_id.mirror = 0;
	if (mlx4_is_bonded(dev)) {
		err = mlx4_multicast_attach(mdev->dev, &mqp->mqp, gid->raw,
					    (mqp->port == 1) ? 2 : 1,
					    !!(mqp->flags &
					    MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK),
					    prot, &reg_id.mirror);
		if (err)
			goto err_add;
	}

	err = add_gid_entry(ibqp, gid);
	if (err)
		goto err_add;

	if (ib_steering) {
		memcpy(ib_steering->gid.raw, gid->raw, 16);
		ib_steering->reg_id = reg_id;
		mutex_lock(&mqp->mutex);
		list_add(&ib_steering->list, &mqp->steering_rules);
		mutex_unlock(&mqp->mutex);
	}
	return 0;

err_add:
	mlx4_multicast_detach(mdev->dev, &mqp->mqp, gid->raw,
			      prot, reg_id.id);
	if (reg_id.mirror)
		mlx4_multicast_detach(mdev->dev, &mqp->mqp, gid->raw,
				      prot, reg_id.mirror);
err_malloc:
	kfree(ib_steering);

	return err;
}