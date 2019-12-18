#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_user_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  rx_suspend; } ;
struct TYPE_7__ {scalar_t__ state; } ;
struct siw_qp {TYPE_3__ rx_stream; int /*<<< orphan*/  state_lock; TYPE_2__ attrs; } ;
struct TYPE_6__ {struct siw_qp* data; } ;
struct TYPE_9__ {int count; TYPE_1__ arg; } ;
typedef  TYPE_4__ read_descriptor_t ;

/* Variables and functions */
 scalar_t__ SIW_QP_STATE_RTS ; 
 scalar_t__ down_read_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_dbg_qp (struct siw_qp*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_tcp_rx_data ; 
 struct siw_qp* sk_to_qp (struct sock*) ; 
 int /*<<< orphan*/  tcp_read_sock (struct sock*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void siw_qp_llp_data_ready(struct sock *sk)
{
	struct siw_qp *qp;

	read_lock(&sk->sk_callback_lock);

	if (unlikely(!sk->sk_user_data || !sk_to_qp(sk)))
		goto done;

	qp = sk_to_qp(sk);

	if (likely(!qp->rx_stream.rx_suspend &&
		   down_read_trylock(&qp->state_lock))) {
		read_descriptor_t rd_desc = { .arg.data = qp, .count = 1 };

		if (likely(qp->attrs.state == SIW_QP_STATE_RTS))
			/*
			 * Implements data receive operation during
			 * socket callback. TCP gracefully catches
			 * the case where there is nothing to receive
			 * (not calling siw_tcp_rx_data() then).
			 */
			tcp_read_sock(sk, &rd_desc, siw_tcp_rx_data);

		up_read(&qp->state_lock);
	} else {
		siw_dbg_qp(qp, "unable to process RX, suspend: %d\n",
			   qp->rx_stream.rx_suspend);
	}
done:
	read_unlock(&sk->sk_callback_lock);
}