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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct tls_context {int dummy; } ;
struct sock {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_tls_offload_context_rx {int /*<<< orphan*/  handle; } ;
struct mlx5e_priv {TYPE_2__* tls; int /*<<< orphan*/  mdev; } ;
typedef  enum tls_offload_ctx_dir { ____Placeholder_tls_offload_ctx_dir } tls_offload_ctx_dir ;
struct TYPE_3__ {int /*<<< orphan*/  rx_tls_resync_reply; } ;
struct TYPE_4__ {TYPE_1__ sw_stats; } ;

/* Variables and functions */
 int EINVAL ; 
 int TLS_OFFLOAD_CTX_DIR_RX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_accel_tls_resync_rx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5e_tls_offload_context_rx* mlx5e_get_tls_rx_context (struct tls_context*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 

__attribute__((used)) static int mlx5e_tls_resync(struct net_device *netdev, struct sock *sk,
			    u32 seq, u8 *rcd_sn_data,
			    enum tls_offload_ctx_dir direction)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5e_tls_offload_context_rx *rx_ctx;
	u64 rcd_sn = *(u64 *)rcd_sn_data;

	if (WARN_ON_ONCE(direction != TLS_OFFLOAD_CTX_DIR_RX))
		return -EINVAL;
	rx_ctx = mlx5e_get_tls_rx_context(tls_ctx);

	netdev_info(netdev, "resyncing seq %d rcd %lld\n", seq,
		    be64_to_cpu(rcd_sn));
	mlx5_accel_tls_resync_rx(priv->mdev, rx_ctx->handle, seq, rcd_sn);
	atomic64_inc(&priv->tls->sw_stats.rx_tls_resync_reply);

	return 0;
}