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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct tls12_crypto_info_aes_gcm_128 {int dummy; } ;
struct mlx5e_ktls_offload_context_tx {int key_id; struct tls12_crypto_info_aes_gcm_128 crypto_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_INFO_FIELDS ; 
 int MLX5E_ENCRYPTION_STANDARD_TLS ; 
 int MLX5E_STATIC_PARAMS_CONTEXT_TLS_1_2 ; 
 char* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,char*) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int,int) ; 
 int const_1 ; 
 int const_2 ; 
 int dek_index ; 
 int encryption_standard ; 
 char* initial_record_number ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_static_params ; 

__attribute__((used)) static void
fill_static_params_ctx(void *ctx, struct mlx5e_ktls_offload_context_tx *priv_tx)
{
	struct tls12_crypto_info_aes_gcm_128 *info = &priv_tx->crypto_info;
	char *initial_rn, *gcm_iv;
	u16 salt_sz, rec_seq_sz;
	char *salt, *rec_seq;
	u8 tls_version;

	EXTRACT_INFO_FIELDS;

	gcm_iv      = MLX5_ADDR_OF(tls_static_params, ctx, gcm_iv);
	initial_rn  = MLX5_ADDR_OF(tls_static_params, ctx, initial_record_number);

	memcpy(gcm_iv,      salt,    salt_sz);
	memcpy(initial_rn,  rec_seq, rec_seq_sz);

	tls_version = MLX5E_STATIC_PARAMS_CONTEXT_TLS_1_2;

	MLX5_SET(tls_static_params, ctx, tls_version, tls_version);
	MLX5_SET(tls_static_params, ctx, const_1, 1);
	MLX5_SET(tls_static_params, ctx, const_2, 2);
	MLX5_SET(tls_static_params, ctx, encryption_standard,
		 MLX5E_ENCRYPTION_STANDARD_TLS);
	MLX5_SET(tls_static_params, ctx, dek_index, priv_tx->key_id);
}