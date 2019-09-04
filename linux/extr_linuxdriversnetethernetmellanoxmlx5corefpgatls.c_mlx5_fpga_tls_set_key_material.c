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
struct tls_crypto_info {int cipher_type; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EINVAL ; 
 int MLX5_ACCEL_TLS_AES_GCM128 ; 
#define  TLS_CIPHER_AES_GCM_128 128 
 int /*<<< orphan*/  mlx5_fpga_tls_set_aes_gcm128_ctx (void*,struct tls_crypto_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_fpga_tls_set_key_material(void *cmd, u32 caps,
					  struct tls_crypto_info *crypto_info)
{
	__be64 rcd_sn;

	switch (crypto_info->cipher_type) {
	case TLS_CIPHER_AES_GCM_128:
		if (!(caps & MLX5_ACCEL_TLS_AES_GCM128))
			return -EINVAL;
		mlx5_fpga_tls_set_aes_gcm128_ctx(cmd, crypto_info, &rcd_sn);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}