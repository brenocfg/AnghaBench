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
struct tls_crypto_info {int dummy; } ;
struct tls_context {int dummy; } ;
struct sock {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_tls_offload_context_tx {int /*<<< orphan*/  expected_seq; void* swid; } ;
struct mlx5e_tls_offload_context_rx {void* handle; } ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum tls_offload_ctx_dir { ____Placeholder_tls_offload_ctx_dir } tls_offload_ctx_dir ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int TLS_OFFLOAD_CTX_DIR_TX ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_accel_tls_add_flow (struct mlx5_core_dev*,void*,struct tls_crypto_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_accel_tls_device_caps (struct mlx5_core_dev*) ; 
 struct mlx5e_tls_offload_context_rx* mlx5e_get_tls_rx_context (struct tls_context*) ; 
 struct mlx5e_tls_offload_context_tx* mlx5e_get_tls_tx_context (struct tls_context*) ; 
 int mlx5e_tls_set_flow (void*,struct sock*,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tls_flow ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 

__attribute__((used)) static int mlx5e_tls_add(struct net_device *netdev, struct sock *sk,
			 enum tls_offload_ctx_dir direction,
			 struct tls_crypto_info *crypto_info,
			 u32 start_offload_tcp_sn)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct mlx5_core_dev *mdev = priv->mdev;
	u32 caps = mlx5_accel_tls_device_caps(mdev);
	int ret = -ENOMEM;
	void *flow;
	u32 swid;

	flow = kzalloc(MLX5_ST_SZ_BYTES(tls_flow), GFP_KERNEL);
	if (!flow)
		return ret;

	ret = mlx5e_tls_set_flow(flow, sk, caps);
	if (ret)
		goto free_flow;

	ret = mlx5_accel_tls_add_flow(mdev, flow, crypto_info,
				      start_offload_tcp_sn, &swid,
				      direction == TLS_OFFLOAD_CTX_DIR_TX);
	if (ret < 0)
		goto free_flow;

	if (direction == TLS_OFFLOAD_CTX_DIR_TX) {
		struct mlx5e_tls_offload_context_tx *tx_ctx =
		    mlx5e_get_tls_tx_context(tls_ctx);

		tx_ctx->swid = htonl(swid);
		tx_ctx->expected_seq = start_offload_tcp_sn;
	} else {
		struct mlx5e_tls_offload_context_rx *rx_ctx =
		    mlx5e_get_tls_rx_context(tls_ctx);

		rx_ctx->handle = htonl(swid);
	}

	return 0;
free_flow:
	kfree(flow);
	return ret;
}