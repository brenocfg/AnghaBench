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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MLX5_ADDR_OF (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5_REG_MCDA ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcda_reg ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int mlx5_core_access_reg (struct mlx5_core_dev*,int*,int,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mlx5_reg_mcda_set(struct mlx5_core_dev *dev,
			     u32 update_handle,
			     u32 offset, u16 size,
			     u8 *data)
{
	int err, in_size = MLX5_ST_SZ_BYTES(mcda_reg) + size;
	u32 out[MLX5_ST_SZ_DW(mcda_reg)];
	int i, j, dw_size = size >> 2;
	__be32 data_element;
	u32 *in;

	in = kzalloc(in_size, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	MLX5_SET(mcda_reg, in, update_handle, update_handle);
	MLX5_SET(mcda_reg, in, offset, offset);
	MLX5_SET(mcda_reg, in, size, size);

	for (i = 0; i < dw_size; i++) {
		j = i * 4;
		data_element = htonl(*(u32 *)&data[j]);
		memcpy(MLX5_ADDR_OF(mcda_reg, in, data) + j, &data_element, 4);
	}

	err = mlx5_core_access_reg(dev, in, in_size, out,
				   sizeof(out), MLX5_REG_MCDA, 0, 1);
	kfree(in);
	return err;
}