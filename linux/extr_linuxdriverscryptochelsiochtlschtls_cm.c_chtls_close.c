#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_state; TYPE_2__* sk_prot; int /*<<< orphan*/  sk_lingertime; int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_shutdown; } ;
struct sk_buff {int dummy; } ;
struct cpl_abort_req {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk_recv_queue; } ;
struct chtls_sock {TYPE_1__ tlshws; } ;
struct TYPE_6__ {scalar_t__ linger2; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* disconnect ) (struct sock*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_ABORT_SEND_RST ; 
 int /*<<< orphan*/  CSK_ABORT_SHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SOCK_LINGER ; 
 int TCP_CLOSE ; 
 int TCP_FIN_WAIT2 ; 
 int TCP_SYN_SENT ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  chtls_close_conn (struct sock*) ; 
 int /*<<< orphan*/  chtls_purge_receive_queue (struct sock*) ; 
 int /*<<< orphan*/  chtls_purge_recv_queue (struct sock*) ; 
 int /*<<< orphan*/  chtls_send_reset (struct sock*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  csk_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_csk_destroy_sock (struct sock*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 scalar_t__ make_close_transition (struct sock*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  release_tcp_port (struct sock*) ; 
 int /*<<< orphan*/  sk_stream_wait_close (struct sock*,long) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ) ; 
 TYPE_3__* tcp_sk (struct sock*) ; 

void chtls_close(struct sock *sk, long timeout)
{
	int data_lost, prev_state;
	struct chtls_sock *csk;

	csk = rcu_dereference_sk_user_data(sk);

	lock_sock(sk);
	sk->sk_shutdown |= SHUTDOWN_MASK;

	data_lost = skb_queue_len(&sk->sk_receive_queue);
	data_lost |= skb_queue_len(&csk->tlshws.sk_recv_queue);
	chtls_purge_recv_queue(sk);
	chtls_purge_receive_queue(sk);

	if (sk->sk_state == TCP_CLOSE) {
		goto wait;
	} else if (data_lost || sk->sk_state == TCP_SYN_SENT) {
		chtls_send_reset(sk, CPL_ABORT_SEND_RST, NULL);
		release_tcp_port(sk);
		goto unlock;
	} else if (sock_flag(sk, SOCK_LINGER) && !sk->sk_lingertime) {
		sk->sk_prot->disconnect(sk, 0);
	} else if (make_close_transition(sk)) {
		chtls_close_conn(sk);
	}
wait:
	if (timeout)
		sk_stream_wait_close(sk, timeout);

unlock:
	prev_state = sk->sk_state;
	sock_hold(sk);
	sock_orphan(sk);

	release_sock(sk);

	local_bh_disable();
	bh_lock_sock(sk);

	if (prev_state != TCP_CLOSE && sk->sk_state == TCP_CLOSE)
		goto out;

	if (sk->sk_state == TCP_FIN_WAIT2 && tcp_sk(sk)->linger2 < 0 &&
	    !csk_flag(sk, CSK_ABORT_SHUTDOWN)) {
		struct sk_buff *skb;

		skb = alloc_skb(sizeof(struct cpl_abort_req), GFP_ATOMIC);
		if (skb)
			chtls_send_reset(sk, CPL_ABORT_SEND_RST, skb);
	}

	if (sk->sk_state == TCP_CLOSE)
		inet_csk_destroy_sock(sk);

out:
	bh_unlock_sock(sk);
	local_bh_enable();
	sock_put(sk);
}