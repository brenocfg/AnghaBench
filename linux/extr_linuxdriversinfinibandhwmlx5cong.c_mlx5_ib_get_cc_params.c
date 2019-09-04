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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum mlx5_ib_cong_node_type { ____Placeholder_mlx5_ib_cong_node_type } mlx5_ib_cong_node_type ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  congestion_parameters ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_query_cong_params (struct mlx5_core_dev*,int,void*,int) ; 
 int /*<<< orphan*/  mlx5_get_cc_param_val (void*,int) ; 
 struct mlx5_core_dev* mlx5_ib_get_native_port_mdev (struct mlx5_ib_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int mlx5_ib_param_to_node (int) ; 
 int /*<<< orphan*/  mlx5_ib_put_native_port_mdev (struct mlx5_ib_dev*,scalar_t__) ; 
 int /*<<< orphan*/  query_cong_params_out ; 

__attribute__((used)) static int mlx5_ib_get_cc_params(struct mlx5_ib_dev *dev, u8 port_num,
				 int offset, u32 *var)
{
	int outlen = MLX5_ST_SZ_BYTES(query_cong_params_out);
	void *out;
	void *field;
	int err;
	enum mlx5_ib_cong_node_type node;
	struct mlx5_core_dev *mdev;

	/* Takes a 1-based port number */
	mdev = mlx5_ib_get_native_port_mdev(dev, port_num + 1, NULL);
	if (!mdev)
		return -ENODEV;

	out = kvzalloc(outlen, GFP_KERNEL);
	if (!out) {
		err = -ENOMEM;
		goto alloc_err;
	}

	node = mlx5_ib_param_to_node(offset);

	err = mlx5_cmd_query_cong_params(mdev, node, out, outlen);
	if (err)
		goto free;

	field = MLX5_ADDR_OF(query_cong_params_out, out, congestion_parameters);
	*var = mlx5_get_cc_param_val(field, offset);

free:
	kvfree(out);
alloc_err:
	mlx5_ib_put_native_port_mdev(dev, port_num + 1);
	return err;
}