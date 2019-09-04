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
typedef  scalar_t__ u16 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5E_UMR_WQE_INLINE_SZ ; 
 scalar_t__ MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_wqe_sz_sq ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  reg_umr_sq ; 
 int /*<<< orphan*/  striding_rq ; 
 int /*<<< orphan*/  umr_ptr_rlky ; 

bool mlx5e_check_fragmented_striding_rq_cap(struct mlx5_core_dev *mdev)
{
	bool striding_rq_umr = MLX5_CAP_GEN(mdev, striding_rq) &&
		MLX5_CAP_GEN(mdev, umr_ptr_rlky) &&
		MLX5_CAP_ETH(mdev, reg_umr_sq);
	u16 max_wqe_sz_cap = MLX5_CAP_GEN(mdev, max_wqe_sz_sq);
	bool inline_umr = MLX5E_UMR_WQE_INLINE_SZ <= max_wqe_sz_cap;

	if (!striding_rq_umr)
		return false;
	if (!inline_umr) {
		mlx5_core_warn(mdev, "Cannot support Striding RQ: UMR WQE size (%d) exceeds maximum supported (%d).\n",
			       (int)MLX5E_UMR_WQE_INLINE_SZ, max_wqe_sz_cap);
		return false;
	}
	return true;
}