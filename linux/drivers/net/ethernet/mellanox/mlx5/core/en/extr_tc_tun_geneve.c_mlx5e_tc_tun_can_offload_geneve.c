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
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_FLEX_PROTO_GENEVE ; 
 int /*<<< orphan*/  flex_parser_protocols ; 

__attribute__((used)) static bool mlx5e_tc_tun_can_offload_geneve(struct mlx5e_priv *priv)
{
	return !!(MLX5_CAP_GEN(priv->mdev, flex_parser_protocols) & MLX5_FLEX_PROTO_GENEVE);
}