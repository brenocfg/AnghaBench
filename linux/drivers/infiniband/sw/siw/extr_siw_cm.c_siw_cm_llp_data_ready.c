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
struct sock {int /*<<< orphan*/  sk_callback_lock; } ;
struct siw_cep {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIW_CM_WORK_READ_MPAHDR ; 
#define  SIW_EPSTATE_AWAIT_MPAREP 131 
#define  SIW_EPSTATE_AWAIT_MPAREQ 130 
#define  SIW_EPSTATE_LISTENING 129 
#define  SIW_EPSTATE_RDMA_MODE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_cm_queue_work (struct siw_cep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_dbg_cep (struct siw_cep*,char*,int) ; 
 struct siw_cep* sk_to_cep (struct sock*) ; 

__attribute__((used)) static void siw_cm_llp_data_ready(struct sock *sk)
{
	struct siw_cep *cep;

	read_lock(&sk->sk_callback_lock);

	cep = sk_to_cep(sk);
	if (!cep) {
		WARN_ON(1);
		goto out;
	}
	siw_dbg_cep(cep, "state: %d\n", cep->state);

	switch (cep->state) {
	case SIW_EPSTATE_RDMA_MODE:
		/* fall through */
	case SIW_EPSTATE_LISTENING:
		break;

	case SIW_EPSTATE_AWAIT_MPAREQ:
		/* fall through */
	case SIW_EPSTATE_AWAIT_MPAREP:
		siw_cm_queue_work(cep, SIW_CM_WORK_READ_MPAHDR);
		break;

	default:
		siw_dbg_cep(cep, "unexpected data, state %d\n", cep->state);
		break;
	}
out:
	read_unlock(&sk->sk_callback_lock);
}