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
struct t3cdev {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cxgbi_sock {int /*<<< orphan*/  lock; int /*<<< orphan*/  err; int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;
struct cpl_abort_req_rss {scalar_t__ status; } ;

/* Variables and functions */
 int CPL_ABORT_NO_RST ; 
 scalar_t__ CPL_ERR_PERSIST_NEG_ADVICE ; 
 scalar_t__ CPL_ERR_RTX_NEG_ADVICE ; 
 int /*<<< orphan*/  CTPF_ABORT_REQ_RCVD ; 
 int /*<<< orphan*/  CTPF_ABORT_RPL_PENDING ; 
 int /*<<< orphan*/  CTP_ABORTING ; 
 int CXGBI_DBG_SOCK ; 
 int CXGBI_DBG_TOE ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  abort_status_to_errno (struct cxgbi_sock*,scalar_t__,int*) ; 
 struct cpl_abort_req_rss* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgbi_sock_clear_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_closed (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_set_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_set_state (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_abort_rpl (struct cxgbi_sock*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_abort_req(struct t3cdev *cdev, struct sk_buff *skb, void *ctx)
{
	const struct cpl_abort_req_rss *req = cplhdr(skb);
	struct cxgbi_sock *csk = ctx;
	int rst_status = CPL_ABORT_NO_RST;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u.\n",
		csk, csk->state, csk->flags, csk->tid);

	if (req->status == CPL_ERR_RTX_NEG_ADVICE ||
	    req->status == CPL_ERR_PERSIST_NEG_ADVICE) {
		goto done;
	}

	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);

	if (!cxgbi_sock_flag(csk, CTPF_ABORT_REQ_RCVD)) {
		cxgbi_sock_set_flag(csk, CTPF_ABORT_REQ_RCVD);
		cxgbi_sock_set_state(csk, CTP_ABORTING);
		goto out;
	}

	cxgbi_sock_clear_flag(csk, CTPF_ABORT_REQ_RCVD);
	send_abort_rpl(csk, rst_status);

	if (!cxgbi_sock_flag(csk, CTPF_ABORT_RPL_PENDING)) {
		csk->err = abort_status_to_errno(csk, req->status, &rst_status);
		cxgbi_sock_closed(csk);
	}

out:
	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
done:
	__kfree_skb(skb);
	return 0;
}