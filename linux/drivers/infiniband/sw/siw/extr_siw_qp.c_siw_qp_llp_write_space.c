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
struct sock {int /*<<< orphan*/  sk_callback_lock; TYPE_1__* sk_socket; } ;
struct siw_cep {int /*<<< orphan*/  qp; int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_sq_start (int /*<<< orphan*/ ) ; 
 struct siw_cep* sk_to_cep (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void siw_qp_llp_write_space(struct sock *sk)
{
	struct siw_cep *cep;

	read_lock(&sk->sk_callback_lock);

	cep  = sk_to_cep(sk);
	if (cep) {
		cep->sk_write_space(sk);

		if (!test_bit(SOCK_NOSPACE, &sk->sk_socket->flags))
			(void)siw_sq_start(cep->qp);
	}

	read_unlock(&sk->sk_callback_lock);
}