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
typedef  int u32 ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; int /*<<< orphan*/  netdev; } ;
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */
 int MLX5E_LINK_MODES_NUMBER ; 
 int MLX5E_PROT_MASK (int) ; 
 int MLX5_GET (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  MLX5_PTYS_EN ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_query_port_ptys (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptys_reg ; 

__attribute__((used)) static int mlx5e_test_link_speed(struct mlx5e_priv *priv)
{
	u32 out[MLX5_ST_SZ_DW(ptys_reg)];
	u32 eth_proto_oper;
	int i;

	if (!netif_carrier_ok(priv->netdev))
		return 1;

	if (mlx5_query_port_ptys(priv->mdev, out, sizeof(out), MLX5_PTYS_EN, 1))
		return 1;

	eth_proto_oper = MLX5_GET(ptys_reg, out, eth_proto_oper);
	for (i = 0; i < MLX5E_LINK_MODES_NUMBER; i++) {
		if (eth_proto_oper & MLX5E_PROT_MASK(i))
			return 0;
	}
	return 1;
}