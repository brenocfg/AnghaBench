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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum mlx5_ib_cong_node_type { ____Placeholder_mlx5_ib_cong_node_type } mlx5_ib_cong_node_type ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_CMD_OP_MODIFY_CONG_PARAMS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cong_protocol ; 
 int /*<<< orphan*/  congestion_parameters ; 
 int /*<<< orphan*/  field_select ; 
 int /*<<< orphan*/  field_select_r_roce_rp ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_modify_cong_params (struct mlx5_core_dev*,void*,int) ; 
 struct mlx5_core_dev* mlx5_ib_get_native_port_mdev (struct mlx5_ib_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int mlx5_ib_param_to_node (int) ; 
 int /*<<< orphan*/  mlx5_ib_put_native_port_mdev (struct mlx5_ib_dev*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5_ib_set_cc_param_mask_val (void*,int,int,int*) ; 
 int /*<<< orphan*/  modify_cong_params_in ; 
 int /*<<< orphan*/  opcode ; 

__attribute__((used)) static int mlx5_ib_set_cc_params(struct mlx5_ib_dev *dev, u8 port_num,
				 int offset, u32 var)
{
	int inlen = MLX5_ST_SZ_BYTES(modify_cong_params_in);
	void *in;
	void *field;
	enum mlx5_ib_cong_node_type node;
	struct mlx5_core_dev *mdev;
	u32 attr_mask = 0;
	int err;

	/* Takes a 1-based port number */
	mdev = mlx5_ib_get_native_port_mdev(dev, port_num + 1, NULL);
	if (!mdev)
		return -ENODEV;

	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in) {
		err = -ENOMEM;
		goto alloc_err;
	}

	MLX5_SET(modify_cong_params_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_CONG_PARAMS);

	node = mlx5_ib_param_to_node(offset);
	MLX5_SET(modify_cong_params_in, in, cong_protocol, node);

	field = MLX5_ADDR_OF(modify_cong_params_in, in, congestion_parameters);
	mlx5_ib_set_cc_param_mask_val(field, offset, var, &attr_mask);

	field = MLX5_ADDR_OF(modify_cong_params_in, in, field_select);
	MLX5_SET(field_select_r_roce_rp, field, field_select_r_roce_rp,
		 attr_mask);

	err = mlx5_cmd_modify_cong_params(mdev, in, inlen);
	kvfree(in);
alloc_err:
	mlx5_ib_put_native_port_mdev(dev, port_num + 1);
	return err;
}