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
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int EPERM ; 
 int MLX5_PTYS_EN ; 
 int /*<<< orphan*/  MLX5_REG_PTYS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_proto_admin ; 
 int /*<<< orphan*/  ext_eth_proto_admin ; 
 int /*<<< orphan*/  local_port ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int mlx5_core_access_reg (struct mlx5_core_dev*,int*,int,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_port_query_eth_autoneg (struct mlx5_core_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proto_mask ; 
 int /*<<< orphan*/  ptys_reg ; 

int mlx5_port_set_eth_ptys(struct mlx5_core_dev *dev, bool an_disable,
			   u32 proto_admin, bool ext)
{
	u32 out[MLX5_ST_SZ_DW(ptys_reg)];
	u32 in[MLX5_ST_SZ_DW(ptys_reg)];
	u8 an_disable_admin;
	u8 an_disable_cap;
	u8 an_status;

	mlx5_port_query_eth_autoneg(dev, &an_status, &an_disable_cap,
				    &an_disable_admin);
	if (!an_disable_cap && an_disable)
		return -EPERM;

	memset(in, 0, sizeof(in));

	MLX5_SET(ptys_reg, in, local_port, 1);
	MLX5_SET(ptys_reg, in, an_disable_admin, an_disable);
	MLX5_SET(ptys_reg, in, proto_mask, MLX5_PTYS_EN);
	if (ext)
		MLX5_SET(ptys_reg, in, ext_eth_proto_admin, proto_admin);
	else
		MLX5_SET(ptys_reg, in, eth_proto_admin, proto_admin);

	return mlx5_core_access_reg(dev, in, sizeof(in), out,
			    sizeof(out), MLX5_REG_PTYS, 0, 1);
}