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
struct sock {struct gtp_dev* sk_user_data; } ;
struct gtp_dev {int /*<<< orphan*/ * sk1u; struct sock* sk0; } ;
struct TYPE_2__ {scalar_t__ encap_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  rcu_assign_sk_user_data (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 TYPE_1__* udp_sk (struct sock*) ; 

__attribute__((used)) static void __gtp_encap_destroy(struct sock *sk)
{
	struct gtp_dev *gtp;

	lock_sock(sk);
	gtp = sk->sk_user_data;
	if (gtp) {
		if (gtp->sk0 == sk)
			gtp->sk0 = NULL;
		else
			gtp->sk1u = NULL;
		udp_sk(sk)->encap_type = 0;
		rcu_assign_sk_user_data(sk, NULL);
		sock_put(sk);
	}
	release_sock(sk);
}