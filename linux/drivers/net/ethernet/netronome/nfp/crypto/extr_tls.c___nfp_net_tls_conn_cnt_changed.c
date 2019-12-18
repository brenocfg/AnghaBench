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
struct TYPE_2__ {int ktls_tx; } ;
struct nfp_net {int ktls_tx_conn_cnt; int ktls_rx_conn_cnt; TYPE_1__ dp; } ;
typedef  enum tls_offload_ctx_dir { ____Placeholder_tls_offload_ctx_dir } tls_offload_ctx_dir ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_DEC ; 
 int /*<<< orphan*/  NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_ENC ; 
 int TLS_OFFLOAD_CTX_DIR_TX ; 
 int /*<<< orphan*/  nfp_net_crypto_set_op (struct nfp_net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
__nfp_net_tls_conn_cnt_changed(struct nfp_net *nn, int add,
			       enum tls_offload_ctx_dir direction)
{
	u8 opcode;
	int cnt;

	if (direction == TLS_OFFLOAD_CTX_DIR_TX) {
		opcode = NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_ENC;
		nn->ktls_tx_conn_cnt += add;
		cnt = nn->ktls_tx_conn_cnt;
		nn->dp.ktls_tx = !!nn->ktls_tx_conn_cnt;
	} else {
		opcode = NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_DEC;
		nn->ktls_rx_conn_cnt += add;
		cnt = nn->ktls_rx_conn_cnt;
	}

	/* Care only about 0 -> 1 and 1 -> 0 transitions */
	if (cnt > 1)
		return false;

	nfp_net_crypto_set_op(nn, opcode, cnt);
	return true;
}