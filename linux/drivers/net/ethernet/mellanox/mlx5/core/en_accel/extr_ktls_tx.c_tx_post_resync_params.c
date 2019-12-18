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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct tls12_crypto_info_aes_gcm_128 {char* rec_seq; } ;
struct mlx5e_txqsq {int dummy; } ;
struct mlx5e_ktls_offload_context_tx {struct tls12_crypto_info_aes_gcm_128 crypto_info; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5e_ktls_tx_post_param_wqes (struct mlx5e_txqsq*,struct mlx5e_ktls_offload_context_tx*,int,int) ; 

__attribute__((used)) static void
tx_post_resync_params(struct mlx5e_txqsq *sq,
		      struct mlx5e_ktls_offload_context_tx *priv_tx,
		      u64 rcd_sn)
{
	struct tls12_crypto_info_aes_gcm_128 *info = &priv_tx->crypto_info;
	__be64 rn_be = cpu_to_be64(rcd_sn);
	bool skip_static_post;
	u16 rec_seq_sz;
	char *rec_seq;

	rec_seq = info->rec_seq;
	rec_seq_sz = sizeof(info->rec_seq);

	skip_static_post = !memcmp(rec_seq, &rn_be, rec_seq_sz);
	if (!skip_static_post)
		memcpy(rec_seq, &rn_be, rec_seq_sz);

	mlx5e_ktls_tx_post_param_wqes(sq, priv_tx, skip_static_post, true);
}