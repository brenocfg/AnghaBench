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

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  chtls_purge_receive_queue (struct sock*) ; 
 int /*<<< orphan*/  sk_wakeup_sleepers (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_done (struct sock*) ; 

__attribute__((used)) static void chtls_conn_done(struct sock *sk)
{
	if (sock_flag(sk, SOCK_DEAD))
		chtls_purge_receive_queue(sk);
	sk_wakeup_sleepers(sk, 0);
	tcp_done(sk);
}