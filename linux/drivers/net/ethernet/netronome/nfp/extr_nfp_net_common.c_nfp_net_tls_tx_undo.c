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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  sk; } ;
struct nfp_net_tls_offload_ctx {scalar_t__ next_seq; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_OFFLOAD_CTX_DIR_TX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 TYPE_1__* tcp_hdr (struct sk_buff*) ; 
 scalar_t__ tcp_hdrlen (struct sk_buff*) ; 
 struct nfp_net_tls_offload_ctx* tls_driver_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_is_sk_tx_device_offloaded (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_tls_tx_undo(struct sk_buff *skb, u64 tls_handle)
{
#ifdef CONFIG_TLS_DEVICE
	struct nfp_net_tls_offload_ctx *ntls;
	u32 datalen, seq;

	if (!tls_handle)
		return;
	if (WARN_ON_ONCE(!skb->sk || !tls_is_sk_tx_device_offloaded(skb->sk)))
		return;

	datalen = skb->len - (skb_transport_offset(skb) + tcp_hdrlen(skb));
	seq = ntohl(tcp_hdr(skb)->seq);

	ntls = tls_driver_ctx(skb->sk, TLS_OFFLOAD_CTX_DIR_TX);
	if (ntls->next_seq == seq + datalen)
		ntls->next_seq = seq;
	else
		WARN_ON_ONCE(1);
#endif
}