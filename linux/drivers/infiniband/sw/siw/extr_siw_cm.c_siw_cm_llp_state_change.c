#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_state; int /*<<< orphan*/  sk_callback_lock; } ;
struct siw_cep {void (* sk_state_change ) (struct sock*) ;int state; TYPE_2__* qp; } ;
struct TYPE_3__ {int tx_suspend; } ;
struct TYPE_4__ {TYPE_1__ tx_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIW_CM_WORK_ACCEPT ; 
 int /*<<< orphan*/  SIW_CM_WORK_PEER_CLOSE ; 
#define  TCP_CLOSE 130 
#define  TCP_CLOSE_WAIT 129 
#define  TCP_ESTABLISHED 128 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_cm_queue_work (struct siw_cep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_dbg_cep (struct siw_cep*,char*,int) ; 
 struct siw_cep* sk_to_cep (struct sock*) ; 

__attribute__((used)) static void siw_cm_llp_state_change(struct sock *sk)
{
	struct siw_cep *cep;
	void (*orig_state_change)(struct sock *s);

	read_lock(&sk->sk_callback_lock);

	cep = sk_to_cep(sk);
	if (!cep) {
		/* endpoint already disassociated */
		read_unlock(&sk->sk_callback_lock);
		return;
	}
	orig_state_change = cep->sk_state_change;

	siw_dbg_cep(cep, "state: %d\n", cep->state);

	switch (sk->sk_state) {
	case TCP_ESTABLISHED:
		/*
		 * handle accepting socket as special case where only
		 * new connection is possible
		 */
		siw_cm_queue_work(cep, SIW_CM_WORK_ACCEPT);
		break;

	case TCP_CLOSE:
	case TCP_CLOSE_WAIT:
		if (cep->qp)
			cep->qp->tx_ctx.tx_suspend = 1;
		siw_cm_queue_work(cep, SIW_CM_WORK_PEER_CLOSE);
		break;

	default:
		siw_dbg_cep(cep, "unexpected socket state %d\n", sk->sk_state);
	}
	read_unlock(&sk->sk_callback_lock);
	orig_state_change(sk);
}