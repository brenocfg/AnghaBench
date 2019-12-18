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
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_RX_HASH_FN_INVERTED_XOR8 ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_build_indir_tir_ctx_common (struct mlx5e_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_hash_fn ; 

__attribute__((used)) static void mlx5e_build_direct_tir_ctx(struct mlx5e_priv *priv, u32 rqtn, u32 *tirc)
{
	mlx5e_build_indir_tir_ctx_common(priv, rqtn, tirc);
	MLX5_SET(tirc, tirc, rx_hash_fn, MLX5_RX_HASH_FN_INVERTED_XOR8);
}