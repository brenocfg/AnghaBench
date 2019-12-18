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
typedef  void u32 ;
struct mlx5_core_qp {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (void*,void*,void*) ; 
 int MLX5_QP_ENHANCED_ULP_STATELESS_MODE ; 
 int MLX5_QP_PM_MIGRATED ; 
 int MLX5_QP_ST_UD ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 void* ads ; 
 void* create_qp_in ; 
 int /*<<< orphan*/  grh ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_core_create_qp (struct mlx5_core_dev*,struct mlx5_core_qp*,void*,int) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  pm_state ; 
 void* primary_address_path ; 
 int /*<<< orphan*/  st ; 
 int /*<<< orphan*/  ulp_stateless_offload_mode ; 
 int /*<<< orphan*/  vhca_port_num ; 

int mlx5i_create_underlay_qp(struct mlx5_core_dev *mdev, struct mlx5_core_qp *qp)
{
	u32 *in = NULL;
	void *addr_path;
	int ret = 0;
	int inlen;
	void *qpc;

	inlen = MLX5_ST_SZ_BYTES(create_qp_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	qpc = MLX5_ADDR_OF(create_qp_in, in, qpc);
	MLX5_SET(qpc, qpc, st, MLX5_QP_ST_UD);
	MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);
	MLX5_SET(qpc, qpc, ulp_stateless_offload_mode,
		 MLX5_QP_ENHANCED_ULP_STATELESS_MODE);

	addr_path = MLX5_ADDR_OF(qpc, qpc, primary_address_path);
	MLX5_SET(ads, addr_path, vhca_port_num, 1);
	MLX5_SET(ads, addr_path, grh, 1);

	ret = mlx5_core_create_qp(mdev, qp, in, inlen);
	if (ret) {
		mlx5_core_err(mdev, "Failed creating IPoIB QP err : %d\n", ret);
		goto out;
	}

out:
	kvfree(in);
	return ret;
}