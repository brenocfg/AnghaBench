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
struct sock {scalar_t__ sk_state; TYPE_1__* sk_prot; } ;
struct TYPE_2__ {int /*<<< orphan*/  orphan_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSK_RST_ABORTED ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  chtls_conn_done (struct sock*) ; 
 int /*<<< orphan*/  chtls_release_resources (struct sock*) ; 
 int /*<<< orphan*/  cleanup_syn_rcv_conn (struct sock*,struct sock*) ; 
 scalar_t__ csk_flag (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 

__attribute__((used)) static void do_abort_syn_rcv(struct sock *child, struct sock *parent)
{
	/*
	 * If the server is still open we clean up the child connection,
	 * otherwise the server already did the clean up as it was purging
	 * its SYN queue and the skb was just sitting in its backlog.
	 */
	if (likely(parent->sk_state == TCP_LISTEN)) {
		cleanup_syn_rcv_conn(child, parent);
		/* Without the below call to sock_orphan,
		 * we leak the socket resource with syn_flood test
		 * as inet_csk_destroy_sock will not be called
		 * in tcp_done since SOCK_DEAD flag is not set.
		 * Kernel handles this differently where new socket is
		 * created only after 3 way handshake is done.
		 */
		sock_orphan(child);
		percpu_counter_inc((child)->sk_prot->orphan_count);
		chtls_release_resources(child);
		chtls_conn_done(child);
	} else {
		if (csk_flag(child, CSK_RST_ABORTED)) {
			chtls_release_resources(child);
			chtls_conn_done(child);
		}
	}
}