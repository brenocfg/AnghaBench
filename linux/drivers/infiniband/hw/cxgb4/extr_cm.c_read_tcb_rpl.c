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
typedef  int u64 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct cpl_get_tcb_rpl {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct c4iw_ep {int rx_pdu_out_cnt; TYPE_1__ com; int /*<<< orphan*/  srqe_idx; int /*<<< orphan*/  hwtid; } ;
struct c4iw_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_REQ_IN_PROGRESS ; 
 unsigned int GET_TID (struct cpl_get_tcb_rpl*) ; 
 int /*<<< orphan*/  PEER_ABORT_IN_PROGRESS ; 
 int /*<<< orphan*/  TCB_RQ_START_S ; 
 int /*<<< orphan*/  TCB_RQ_START_W ; 
 int /*<<< orphan*/  TCB_T_FLAGS_W ; 
 int TF_RX_PDU_OUT_S ; 
 int TF_RX_PDU_OUT_V (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  c4iw_put_ep (TYPE_1__*) ; 
 struct cpl_get_tcb_rpl* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  finish_peer_abort (struct c4iw_dev*,struct c4iw_ep*) ; 
 struct c4iw_ep* get_ep_from_tid (struct c4iw_dev*,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_tcb (struct c4iw_ep*) ; 
 int /*<<< orphan*/  send_abort_req (struct c4iw_ep*) ; 
 int /*<<< orphan*/  t4_tcb_get_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t4_tcb_get_field64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_tcb_rpl(struct c4iw_dev *dev, struct sk_buff *skb)
{
	struct cpl_get_tcb_rpl *rpl = cplhdr(skb);
	__be64 *tcb = (__be64 *)(rpl + 1);
	unsigned int tid = GET_TID(rpl);
	struct c4iw_ep *ep;
	u64 t_flags_64;
	u32 rx_pdu_out;

	ep = get_ep_from_tid(dev, tid);
	if (!ep)
		return 0;
	/* Examine the TF_RX_PDU_OUT (bit 49 of the t_flags) in order to
	 * determine if there's a rx PDU feedback event pending.
	 *
	 * If that bit is set, it means we'll need to re-read the TCB's
	 * rq_start value. The final value is the one present in a TCB
	 * with the TF_RX_PDU_OUT bit cleared.
	 */

	t_flags_64 = t4_tcb_get_field64(tcb, TCB_T_FLAGS_W);
	rx_pdu_out = (t_flags_64 & TF_RX_PDU_OUT_V(1)) >> TF_RX_PDU_OUT_S;

	c4iw_put_ep(&ep->com); /* from get_ep_from_tid() */
	c4iw_put_ep(&ep->com); /* from read_tcb() */

	/* If TF_RX_PDU_OUT bit is set, re-read the TCB */
	if (rx_pdu_out) {
		if (++ep->rx_pdu_out_cnt >= 2) {
			WARN_ONCE(1, "tcb re-read() reached the guard limit, finishing the cleanup\n");
			goto cleanup;
		}
		read_tcb(ep);
		return 0;
	}

	ep->srqe_idx = t4_tcb_get_field32(tcb, TCB_RQ_START_W, TCB_RQ_START_W,
			TCB_RQ_START_S);
cleanup:
	pr_debug("ep %p tid %u %016x\n", ep, ep->hwtid, ep->srqe_idx);

	if (test_bit(PEER_ABORT_IN_PROGRESS, &ep->com.flags))
		finish_peer_abort(dev, ep);
	else if (test_bit(ABORT_REQ_IN_PROGRESS, &ep->com.flags))
		send_abort_req(ep);
	else
		WARN_ONCE(1, "unexpected state!");

	return 0;
}