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
struct cxgbi_sock {int /*<<< orphan*/  lock; int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTPF_ABORT_REQ_RCVD ; 
 int /*<<< orphan*/  CTPF_ABORT_RPL_PENDING ; 
 int /*<<< orphan*/  CTPF_ABORT_RPL_RCVD ; 
 int /*<<< orphan*/  cxgbi_sock_clear_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_closed (struct cxgbi_sock*) ; 
 scalar_t__ cxgbi_sock_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_set_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void cxgbi_sock_rcv_abort_rpl(struct cxgbi_sock *csk)
{
	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);

	cxgbi_sock_set_flag(csk, CTPF_ABORT_RPL_RCVD);
	if (cxgbi_sock_flag(csk, CTPF_ABORT_RPL_PENDING)) {
		cxgbi_sock_clear_flag(csk, CTPF_ABORT_RPL_PENDING);
		if (cxgbi_sock_flag(csk, CTPF_ABORT_REQ_RCVD))
			pr_err("csk 0x%p,%u,0x%lx,%u,ABT_RPL_RSS.\n",
			       csk, csk->state, csk->flags, csk->tid);
		cxgbi_sock_closed(csk);
	}

	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
}