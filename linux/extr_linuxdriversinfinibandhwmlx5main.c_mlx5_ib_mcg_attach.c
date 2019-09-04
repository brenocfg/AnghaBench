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
union ib_gid {int /*<<< orphan*/  raw; } ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_ib_qp {int flags; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_qp {int /*<<< orphan*/  qp_num; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MLX5_IB_QP_UNDERLAY ; 
 int mlx5_core_attach_mcg (int /*<<< orphan*/ ,union ib_gid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_qp* to_mqp (struct ib_qp*) ; 

__attribute__((used)) static int mlx5_ib_mcg_attach(struct ib_qp *ibqp, union ib_gid *gid, u16 lid)
{
	struct mlx5_ib_dev *dev = to_mdev(ibqp->device);
	struct mlx5_ib_qp *mqp = to_mqp(ibqp);
	int err;

	if (mqp->flags & MLX5_IB_QP_UNDERLAY) {
		mlx5_ib_dbg(dev, "Attaching a multi cast group to underlay QP is not supported\n");
		return -EOPNOTSUPP;
	}

	err = mlx5_core_attach_mcg(dev->mdev, gid, ibqp->qp_num);
	if (err)
		mlx5_ib_warn(dev, "failed attaching QPN 0x%x, MGID %pI6\n",
			     ibqp->qp_num, gid->raw);

	return err;
}