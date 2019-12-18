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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  qp_type; int /*<<< orphan*/  device; } ;
struct TYPE_3__ {int atomic_rd_en; int /*<<< orphan*/  resp_depth; } ;
struct mlx5_ib_qp {TYPE_2__ ibqp; TYPE_1__ trans_qp; } ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_qp_attr {int qp_access_flags; int /*<<< orphan*/  max_dest_rd_atomic; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int IB_ACCESS_REMOTE_ATOMIC ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int IB_QP_ACCESS_FLAGS ; 
 int IB_QP_MAX_DEST_RD_ATOMIC ; 
 int MLX5_ATOMIC_MODE_OFFSET ; 
 int MLX5_QP_BIT_RAE ; 
 int MLX5_QP_BIT_RRE ; 
 int MLX5_QP_BIT_RWE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int get_atomic_mode (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int to_mlx5_access_flags(struct mlx5_ib_qp *qp,
				const struct ib_qp_attr *attr,
				int attr_mask, __be32 *hw_access_flags_be)
{
	u8 dest_rd_atomic;
	u32 access_flags, hw_access_flags = 0;

	struct mlx5_ib_dev *dev = to_mdev(qp->ibqp.device);

	if (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		dest_rd_atomic = attr->max_dest_rd_atomic;
	else
		dest_rd_atomic = qp->trans_qp.resp_depth;

	if (attr_mask & IB_QP_ACCESS_FLAGS)
		access_flags = attr->qp_access_flags;
	else
		access_flags = qp->trans_qp.atomic_rd_en;

	if (!dest_rd_atomic)
		access_flags &= IB_ACCESS_REMOTE_WRITE;

	if (access_flags & IB_ACCESS_REMOTE_READ)
		hw_access_flags |= MLX5_QP_BIT_RRE;
	if (access_flags & IB_ACCESS_REMOTE_ATOMIC) {
		int atomic_mode;

		atomic_mode = get_atomic_mode(dev, qp->ibqp.qp_type);
		if (atomic_mode < 0)
			return -EOPNOTSUPP;

		hw_access_flags |= MLX5_QP_BIT_RAE;
		hw_access_flags |= atomic_mode << MLX5_ATOMIC_MODE_OFFSET;
	}

	if (access_flags & IB_ACCESS_REMOTE_WRITE)
		hw_access_flags |= MLX5_QP_BIT_RWE;

	*hw_access_flags_be = cpu_to_be32(hw_access_flags);

	return 0;
}