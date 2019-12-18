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
struct sock {int /*<<< orphan*/  sk_callback_lock; } ;
struct siw_cep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  siw_cep_put (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_sk_restore_upcalls (struct sock*,struct siw_cep*) ; 
 struct siw_cep* sk_to_cep (struct sock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void siw_socket_disassoc(struct socket *s)
{
	struct sock *sk = s->sk;
	struct siw_cep *cep;

	if (sk) {
		write_lock_bh(&sk->sk_callback_lock);
		cep = sk_to_cep(sk);
		if (cep) {
			siw_sk_restore_upcalls(sk, cep);
			siw_cep_put(cep);
		} else {
			pr_warn("siw: cannot restore sk callbacks: no ep\n");
		}
		write_unlock_bh(&sk->sk_callback_lock);
	} else {
		pr_warn("siw: cannot restore sk callbacks: no sk\n");
	}
}