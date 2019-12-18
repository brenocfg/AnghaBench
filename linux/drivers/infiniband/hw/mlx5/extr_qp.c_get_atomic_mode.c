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
typedef  int u8 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MLX5_ATOMIC_MODE_IB_COMP ; 
 int MLX5_ATOMIC_OPS_CMP_SWAP ; 
 int MLX5_ATOMIC_OPS_EXTENDED_CMP_SWAP ; 
 int MLX5_ATOMIC_OPS_EXTENDED_FETCH_ADD ; 
 int MLX5_ATOMIC_OPS_FETCH_ADD ; 
 void* MLX5_CAP_ATOMIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_IB_QPT_DCT ; 
 int atomic ; 
 int atomic_operations ; 
 int /*<<< orphan*/  atomic_size_dc ; 
 int /*<<< orphan*/  atomic_size_qp ; 
 int atomic_size_to_mode (int) ; 

__attribute__((used)) static int get_atomic_mode(struct mlx5_ib_dev *dev,
			   enum ib_qp_type qp_type)
{
	u8 atomic_operations = MLX5_CAP_ATOMIC(dev->mdev, atomic_operations);
	u8 atomic = MLX5_CAP_GEN(dev->mdev, atomic);
	int atomic_mode = -EOPNOTSUPP;
	int atomic_size_mask;

	if (!atomic)
		return -EOPNOTSUPP;

	if (qp_type == MLX5_IB_QPT_DCT)
		atomic_size_mask = MLX5_CAP_ATOMIC(dev->mdev, atomic_size_dc);
	else
		atomic_size_mask = MLX5_CAP_ATOMIC(dev->mdev, atomic_size_qp);

	if ((atomic_operations & MLX5_ATOMIC_OPS_EXTENDED_CMP_SWAP) ||
	    (atomic_operations & MLX5_ATOMIC_OPS_EXTENDED_FETCH_ADD))
		atomic_mode = atomic_size_to_mode(atomic_size_mask);

	if (atomic_mode <= 0 &&
	    (atomic_operations & MLX5_ATOMIC_OPS_CMP_SWAP &&
	     atomic_operations & MLX5_ATOMIC_OPS_FETCH_ADD))
		atomic_mode = MLX5_ATOMIC_MODE_IB_COMP;

	return atomic_mode;
}