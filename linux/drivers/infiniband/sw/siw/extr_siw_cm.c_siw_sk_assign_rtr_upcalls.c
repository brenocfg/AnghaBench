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
struct sock {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; } ;
struct siw_cep {TYPE_1__* sock; } ;
struct TYPE_2__ {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  siw_qp_llp_write_space ; 
 int /*<<< orphan*/  siw_rtr_data_ready ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void siw_sk_assign_rtr_upcalls(struct siw_cep *cep)
{
	struct sock *sk = cep->sock->sk;

	write_lock_bh(&sk->sk_callback_lock);
	sk->sk_data_ready = siw_rtr_data_ready;
	sk->sk_write_space = siw_qp_llp_write_space;
	write_unlock_bh(&sk->sk_callback_lock);
}