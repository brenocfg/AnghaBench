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
struct sock {TYPE_1__* sk_prot; } ;
struct chtls_sock {int /*<<< orphan*/  kref; int /*<<< orphan*/  ulp_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ULP_MODE_NONE ; 
 int /*<<< orphan*/  chtls_purge_recv_queue (struct sock*) ; 
 int /*<<< orphan*/  chtls_purge_write_queue (struct sock*) ; 
 int /*<<< orphan*/  chtls_sock_release ; 
 int /*<<< orphan*/  free_tls_keyid (struct sock*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 TYPE_1__ tcp_prot ; 

void chtls_destroy_sock(struct sock *sk)
{
	struct chtls_sock *csk;

	csk = rcu_dereference_sk_user_data(sk);
	chtls_purge_recv_queue(sk);
	csk->ulp_mode = ULP_MODE_NONE;
	chtls_purge_write_queue(sk);
	free_tls_keyid(sk);
	kref_put(&csk->kref, chtls_sock_release);
	sk->sk_prot = &tcp_prot;
	sk->sk_prot->destroy(sk);
}