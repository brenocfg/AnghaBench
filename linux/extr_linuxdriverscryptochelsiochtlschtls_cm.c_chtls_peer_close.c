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
struct sock {int sk_shutdown; int sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct sk_buff {int dummy; } ;
struct chtls_sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSK_ABORT_RPL_PENDING ; 
 int /*<<< orphan*/  POLL_HUP ; 
 int /*<<< orphan*/  POLL_IN ; 
 int RCV_SHUTDOWN ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  SOCK_WAKE_WAITD ; 
 int TCP_CLOSE ; 
 int /*<<< orphan*/  TCP_CLOSE_WAIT ; 
 int /*<<< orphan*/  TCP_CLOSING ; 
#define  TCP_ESTABLISHED 131 
#define  TCP_FIN_WAIT1 130 
#define  TCP_FIN_WAIT2 129 
#define  TCP_SYN_RECV 128 
 int /*<<< orphan*/  chtls_conn_done (struct sock*) ; 
 int /*<<< orphan*/  chtls_release_resources (struct sock*) ; 
 int /*<<< orphan*/  chtls_timewait (struct sock*) ; 
 int /*<<< orphan*/  csk_flag_nochk (struct chtls_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  sk_wake_async (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tcp_set_state (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chtls_peer_close(struct sock *sk, struct sk_buff *skb)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);

	sk->sk_shutdown |= RCV_SHUTDOWN;
	sock_set_flag(sk, SOCK_DONE);

	switch (sk->sk_state) {
	case TCP_SYN_RECV:
	case TCP_ESTABLISHED:
		tcp_set_state(sk, TCP_CLOSE_WAIT);
		break;
	case TCP_FIN_WAIT1:
		tcp_set_state(sk, TCP_CLOSING);
		break;
	case TCP_FIN_WAIT2:
		chtls_release_resources(sk);
		if (csk_flag_nochk(csk, CSK_ABORT_RPL_PENDING))
			chtls_conn_done(sk);
		else
			chtls_timewait(sk);
		break;
	default:
		pr_info("cpl_peer_close in bad state %d\n", sk->sk_state);
	}

	if (!sock_flag(sk, SOCK_DEAD)) {
		sk->sk_state_change(sk);
		/* Do not send POLL_HUP for half duplex close. */

		if ((sk->sk_shutdown & SEND_SHUTDOWN) ||
		    sk->sk_state == TCP_CLOSE)
			sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_HUP);
		else
			sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_IN);
	}
}