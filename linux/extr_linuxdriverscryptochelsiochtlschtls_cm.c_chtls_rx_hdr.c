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
struct tlsrx_cmp_hdr {int res_to_mac_error; int /*<<< orphan*/  type; } ;
struct tcp_sock {int /*<<< orphan*/  rcv_nxt; } ;
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int /*<<< orphan*/  data_len; scalar_t__ data; } ;
struct cpl_rx_tls_cmp {int /*<<< orphan*/  pdulength_length; int /*<<< orphan*/  seq; } ;
struct chtls_hws {scalar_t__ pldlen; int /*<<< orphan*/  sk_recv_queue; } ;
struct chtls_sock {struct chtls_hws tlshws; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENT_TYPE_ERROR ; 
 scalar_t__ CPL_RX_TLS_CMP_PDULENGTH_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int TLSRX_HDR_PKT_ERROR_M ; 
 int /*<<< orphan*/  TLS_HEADER_LENGTH ; 
 int /*<<< orphan*/  ULPCB_FLAG_TLS_HDR ; 
 TYPE_1__* ULP_SKB_CB (struct sk_buff*) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_sk_callbacks (struct chtls_sock*) ; 
 int /*<<< orphan*/  chtls_set_hdrlen (struct sk_buff*,scalar_t__) ; 
 struct cpl_rx_tls_cmp* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void chtls_rx_hdr(struct sock *sk, struct sk_buff *skb)
{
	struct tlsrx_cmp_hdr *tls_hdr_pkt;
	struct cpl_rx_tls_cmp *cmp_cpl;
	struct sk_buff *skb_rec;
	struct chtls_sock *csk;
	struct chtls_hws *tlsk;
	struct tcp_sock *tp;

	cmp_cpl = cplhdr(skb);
	csk = rcu_dereference_sk_user_data(sk);
	tlsk = &csk->tlshws;
	tp = tcp_sk(sk);

	ULP_SKB_CB(skb)->seq = ntohl(cmp_cpl->seq);
	ULP_SKB_CB(skb)->flags = 0;

	skb_reset_transport_header(skb);
	__skb_pull(skb, sizeof(*cmp_cpl));
	tls_hdr_pkt = (struct tlsrx_cmp_hdr *)skb->data;
	if (tls_hdr_pkt->res_to_mac_error & TLSRX_HDR_PKT_ERROR_M)
		tls_hdr_pkt->type = CONTENT_TYPE_ERROR;
	if (!skb->data_len)
		__skb_trim(skb, TLS_HEADER_LENGTH);

	tp->rcv_nxt +=
		CPL_RX_TLS_CMP_PDULENGTH_G(ntohl(cmp_cpl->pdulength_length));

	ULP_SKB_CB(skb)->flags |= ULPCB_FLAG_TLS_HDR;
	skb_rec = __skb_dequeue(&tlsk->sk_recv_queue);
	if (!skb_rec) {
		__skb_queue_tail(&sk->sk_receive_queue, skb);
	} else {
		chtls_set_hdrlen(skb, tlsk->pldlen);
		tlsk->pldlen = 0;
		__skb_queue_tail(&sk->sk_receive_queue, skb);
		__skb_queue_tail(&sk->sk_receive_queue, skb_rec);
	}

	if (!sock_flag(sk, SOCK_DEAD)) {
		check_sk_callbacks(csk);
		sk->sk_data_ready(sk);
	}
}