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
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_state; } ;
struct pppox_sock {int dummy; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  PPPOX_DEAD ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  del_chan (struct pppox_sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 struct pppox_sock* pppox_sk (struct sock*) ; 
 int /*<<< orphan*/  pppox_unbind_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int pptp_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct pppox_sock *po;
	int error = 0;

	if (!sk)
		return 0;

	lock_sock(sk);

	if (sock_flag(sk, SOCK_DEAD)) {
		release_sock(sk);
		return -EBADF;
	}

	po = pppox_sk(sk);
	del_chan(po);
	synchronize_rcu();

	pppox_unbind_sock(sk);
	sk->sk_state = PPPOX_DEAD;

	sock_orphan(sk);
	sock->sk = NULL;

	release_sock(sk);
	sock_put(sk);

	return error;
}