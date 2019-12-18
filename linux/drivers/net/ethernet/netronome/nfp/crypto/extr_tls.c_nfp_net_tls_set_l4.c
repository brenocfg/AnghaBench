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
struct sock {int dummy; } ;
struct nfp_crypto_req_add_front {int /*<<< orphan*/  l4_proto; } ;
struct nfp_crypto_req_add_back {int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; } ;
struct inet_sock {int /*<<< orphan*/  inet_sport; int /*<<< orphan*/  inet_dport; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int TLS_OFFLOAD_CTX_DIR_TX ; 
 struct inet_sock* inet_sk (struct sock*) ; 

__attribute__((used)) static void
nfp_net_tls_set_l4(struct nfp_crypto_req_add_front *front,
		   struct nfp_crypto_req_add_back *back, struct sock *sk,
		   int direction)
{
	struct inet_sock *inet = inet_sk(sk);

	front->l4_proto = IPPROTO_TCP;

	if (direction == TLS_OFFLOAD_CTX_DIR_TX) {
		back->src_port = 0;
		back->dst_port = 0;
	} else {
		back->src_port = inet->inet_dport;
		back->dst_port = inet->inet_sport;
	}
}