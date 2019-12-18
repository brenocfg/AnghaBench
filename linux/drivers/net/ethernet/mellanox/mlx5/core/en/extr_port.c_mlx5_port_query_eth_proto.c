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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_port_eth_proto {void* oper; void* admin; void* cap; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */
 int EINVAL ; 
 void* MLX5_GET_ETH_PROTO (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_PTYS_EN ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_proto_admin ; 
 int /*<<< orphan*/  eth_proto_capability ; 
 int /*<<< orphan*/  eth_proto_oper ; 
 int mlx5_query_port_ptys (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptys_reg ; 

int mlx5_port_query_eth_proto(struct mlx5_core_dev *dev, u8 port, bool ext,
			      struct mlx5e_port_eth_proto *eproto)
{
	u32 out[MLX5_ST_SZ_DW(ptys_reg)];
	int err;

	if (!eproto)
		return -EINVAL;

	err = mlx5_query_port_ptys(dev, out, sizeof(out), MLX5_PTYS_EN, port);
	if (err)
		return err;

	eproto->cap   = MLX5_GET_ETH_PROTO(ptys_reg, out, ext,
					   eth_proto_capability);
	eproto->admin = MLX5_GET_ETH_PROTO(ptys_reg, out, ext, eth_proto_admin);
	eproto->oper  = MLX5_GET_ETH_PROTO(ptys_reg, out, ext, eth_proto_oper);
	return 0;
}