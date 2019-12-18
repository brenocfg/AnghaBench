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
struct tls_context {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct mlx5e_ktls_offload_context_tx {int /*<<< orphan*/  tisn; int /*<<< orphan*/  key_id; } ;
typedef  enum tls_offload_ctx_dir { ____Placeholder_tls_offload_ctx_dir } tls_offload_ctx_dir ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (struct mlx5e_ktls_offload_context_tx*) ; 
 int /*<<< orphan*/  mlx5_ktls_destroy_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_destroy_tis (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5e_ktls_offload_context_tx* mlx5e_get_ktls_tx_priv_ctx (struct tls_context*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx5e_ktls_del(struct net_device *netdev,
			   struct tls_context *tls_ctx,
			   enum tls_offload_ctx_dir direction)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5e_ktls_offload_context_tx *tx_priv =
		mlx5e_get_ktls_tx_priv_ctx(tls_ctx);

	mlx5_ktls_destroy_key(priv->mdev, tx_priv->key_id);
	mlx5e_destroy_tis(priv->mdev, tx_priv->tisn);
	kvfree(tx_priv);
}