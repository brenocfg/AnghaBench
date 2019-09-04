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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_CMD_OP_ACCESS_REG ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  access_register_in ; 
 int /*<<< orphan*/  access_register_out ; 
 int /*<<< orphan*/  argument ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int mlx5_cmd_exec (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  op_mod ; 
 int /*<<< orphan*/  opcode ; 
 int /*<<< orphan*/  register_data ; 
 int /*<<< orphan*/  register_id ; 

int mlx5_core_access_reg(struct mlx5_core_dev *dev, void *data_in,
			 int size_in, void *data_out, int size_out,
			 u16 reg_id, int arg, int write)
{
	int outlen = MLX5_ST_SZ_BYTES(access_register_out) + size_out;
	int inlen = MLX5_ST_SZ_BYTES(access_register_in) + size_in;
	int err = -ENOMEM;
	u32 *out = NULL;
	u32 *in = NULL;
	void *data;

	in = kvzalloc(inlen, GFP_KERNEL);
	out = kvzalloc(outlen, GFP_KERNEL);
	if (!in || !out)
		goto out;

	data = MLX5_ADDR_OF(access_register_in, in, register_data);
	memcpy(data, data_in, size_in);

	MLX5_SET(access_register_in, in, opcode, MLX5_CMD_OP_ACCESS_REG);
	MLX5_SET(access_register_in, in, op_mod, !write);
	MLX5_SET(access_register_in, in, argument, arg);
	MLX5_SET(access_register_in, in, register_id, reg_id);

	err = mlx5_cmd_exec(dev, in, inlen, out, outlen);
	if (err)
		goto out;

	data = MLX5_ADDR_OF(access_register_out, out, register_data);
	memcpy(data_out, data, size_out);

out:
	kvfree(out);
	kvfree(in);
	return err;
}