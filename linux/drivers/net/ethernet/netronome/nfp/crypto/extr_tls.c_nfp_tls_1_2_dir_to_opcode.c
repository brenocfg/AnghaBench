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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum tls_offload_ctx_dir { ____Placeholder_tls_offload_ctx_dir } tls_offload_ctx_dir ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_DEC ; 
 int /*<<< orphan*/  NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_ENC ; 
#define  TLS_OFFLOAD_CTX_DIR_RX 129 
#define  TLS_OFFLOAD_CTX_DIR_TX 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static u8 nfp_tls_1_2_dir_to_opcode(enum tls_offload_ctx_dir direction)
{
	switch (direction) {
	case TLS_OFFLOAD_CTX_DIR_TX:
		return NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_ENC;
	case TLS_OFFLOAD_CTX_DIR_RX:
		return NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_DEC;
	default:
		WARN_ON_ONCE(1);
		return 0;
	}
}