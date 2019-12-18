#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_2__ {int crypto_ops; } ;
struct nfp_net {TYPE_1__ tlv_caps; } ;
typedef  enum tls_offload_ctx_dir { ____Placeholder_tls_offload_ctx_dir } tls_offload_ctx_dir ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_DEC ; 
 int /*<<< orphan*/  NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_ENC ; 
#define  TLS_CIPHER_AES_GCM_128 128 
 int TLS_OFFLOAD_CTX_DIR_TX ; 

__attribute__((used)) static bool
nfp_net_cipher_supported(struct nfp_net *nn, u16 cipher_type,
			 enum tls_offload_ctx_dir direction)
{
	u8 bit;

	switch (cipher_type) {
	case TLS_CIPHER_AES_GCM_128:
		if (direction == TLS_OFFLOAD_CTX_DIR_TX)
			bit = NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_ENC;
		else
			bit = NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_DEC;
		break;
	default:
		return false;
	}

	return nn->tlv_caps.crypto_ops & BIT(bit);
}