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
struct tls12_crypto_info_aes_gcm_128 {int dummy; } ;
struct sock {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5e_ktls_offload_context_tx {int /*<<< orphan*/  tisn; int /*<<< orphan*/  key_id; struct tls12_crypto_info_aes_gcm_128 crypto_info; int /*<<< orphan*/  expected_seq; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum tls_offload_ctx_dir { ____Placeholder_tls_offload_ctx_dir } tls_offload_ctx_dir ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TLS_OFFLOAD_CTX_DIR_TX ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kvfree (struct mlx5e_ktls_offload_context_tx*) ; 
 struct mlx5e_ktls_offload_context_tx* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_ktls_create_key (struct mlx5_core_dev*,struct tls_crypto_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_destroy_tis (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5e_ktls_create_tis (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_ktls_tx_offload_set_pending (struct mlx5e_ktls_offload_context_tx*) ; 
 int /*<<< orphan*/  mlx5e_ktls_type_check (struct mlx5_core_dev*,struct tls_crypto_info*) ; 
 int /*<<< orphan*/  mlx5e_set_ktls_tx_priv_ctx (struct tls_context*,struct mlx5e_ktls_offload_context_tx*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 

__attribute__((used)) static int mlx5e_ktls_add(struct net_device *netdev, struct sock *sk,
			  enum tls_offload_ctx_dir direction,
			  struct tls_crypto_info *crypto_info,
			  u32 start_offload_tcp_sn)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5e_ktls_offload_context_tx *tx_priv;
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct mlx5_core_dev *mdev = priv->mdev;
	int err;

	if (WARN_ON(direction != TLS_OFFLOAD_CTX_DIR_TX))
		return -EINVAL;

	if (WARN_ON(!mlx5e_ktls_type_check(mdev, crypto_info)))
		return -EOPNOTSUPP;

	tx_priv = kvzalloc(sizeof(*tx_priv), GFP_KERNEL);
	if (!tx_priv)
		return -ENOMEM;

	tx_priv->expected_seq = start_offload_tcp_sn;
	tx_priv->crypto_info  = *(struct tls12_crypto_info_aes_gcm_128 *)crypto_info;
	mlx5e_set_ktls_tx_priv_ctx(tls_ctx, tx_priv);

	/* tc and underlay_qpn values are not in use for tls tis */
	err = mlx5e_ktls_create_tis(mdev, &tx_priv->tisn);
	if (err)
		goto create_tis_fail;

	err = mlx5_ktls_create_key(mdev, crypto_info, &tx_priv->key_id);
	if (err)
		goto encryption_key_create_fail;

	mlx5e_ktls_tx_offload_set_pending(tx_priv);

	return 0;

encryption_key_create_fail:
	mlx5e_destroy_tis(priv->mdev, tx_priv->tisn);
create_tis_fail:
	kvfree(tx_priv);
	return err;
}