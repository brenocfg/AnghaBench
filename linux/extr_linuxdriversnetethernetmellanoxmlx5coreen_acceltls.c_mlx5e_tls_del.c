#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tls_context {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
typedef  enum tls_offload_ctx_dir { ____Placeholder_tls_offload_ctx_dir } tls_offload_ctx_dir ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  swid; } ;

/* Variables and functions */
 int TLS_OFFLOAD_CTX_DIR_TX ; 
 int /*<<< orphan*/  mlx5_accel_tls_del_flow (int /*<<< orphan*/ ,unsigned int,int) ; 
 TYPE_2__* mlx5e_get_tls_rx_context (struct tls_context*) ; 
 TYPE_1__* mlx5e_get_tls_tx_context (struct tls_context*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_tls_del(struct net_device *netdev,
			  struct tls_context *tls_ctx,
			  enum tls_offload_ctx_dir direction)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	unsigned int handle;

	handle = ntohl((direction == TLS_OFFLOAD_CTX_DIR_TX) ?
		       mlx5e_get_tls_tx_context(tls_ctx)->swid :
		       mlx5e_get_tls_rx_context(tls_ctx)->handle);

	mlx5_accel_tls_del_flow(priv->mdev, handle,
				direction == TLS_OFFLOAD_CTX_DIR_TX);
}