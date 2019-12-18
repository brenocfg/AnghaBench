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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct fc_lport {int /*<<< orphan*/  host; } ;
struct fc_frame {int dummy; } ;
struct fc_exch {scalar_t__ oxid; scalar_t__ rxid; scalar_t__ sid; int esb_stat; int /*<<< orphan*/  ex_lock; int /*<<< orphan*/  ex_refcnt; } ;
struct fc_els_rrq {int /*<<< orphan*/  rrq_rx_id; int /*<<< orphan*/  rrq_ox_id; int /*<<< orphan*/  rrq_s_id; } ;
typedef  enum fc_els_rjt_explan { ____Placeholder_fc_els_rjt_explan } fc_els_rjt_explan ;

/* Variables and functions */
 int ELS_EXPL_INV_LEN ; 
 int ELS_EXPL_OXID_RXID ; 
 int ELS_EXPL_SID ; 
 int /*<<< orphan*/  ELS_RJT_LOGIC ; 
 int ESB_ST_COMPLETE ; 
 int ESB_ST_REC_QUAL ; 
 int /*<<< orphan*/  FC_EXCH_DBG (struct fc_exch*,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ FC_XID_UNKNOWN ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct fc_exch* fc_exch_lookup (struct fc_lport*,scalar_t__) ; 
 int /*<<< orphan*/  fc_exch_release (struct fc_exch*) ; 
 int /*<<< orphan*/  fc_exch_timer_cancel (struct fc_exch*) ; 
 struct fc_els_rrq* fc_frame_payload_get (struct fc_frame*,int) ; 
 scalar_t__ fc_host_port_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_seq_ls_acc (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_seq_ls_rjt (struct fc_frame*,int /*<<< orphan*/ ,int) ; 
 struct fc_lport* fr_dev (struct fc_frame*) ; 
 scalar_t__ ntoh24 (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_exch_els_rrq(struct fc_frame *fp)
{
	struct fc_lport *lport;
	struct fc_exch *ep = NULL;	/* request or subject exchange */
	struct fc_els_rrq *rp;
	u32 sid;
	u16 xid;
	enum fc_els_rjt_explan explan;

	lport = fr_dev(fp);
	rp = fc_frame_payload_get(fp, sizeof(*rp));
	explan = ELS_EXPL_INV_LEN;
	if (!rp)
		goto reject;

	/*
	 * lookup subject exchange.
	 */
	sid = ntoh24(rp->rrq_s_id);		/* subject source */
	xid = fc_host_port_id(lport->host) == sid ?
			ntohs(rp->rrq_ox_id) : ntohs(rp->rrq_rx_id);
	ep = fc_exch_lookup(lport, xid);
	explan = ELS_EXPL_OXID_RXID;
	if (!ep)
		goto reject;
	spin_lock_bh(&ep->ex_lock);
	FC_EXCH_DBG(ep, "RRQ request from %x: xid %x rxid %x oxid %x\n",
		    sid, xid, ntohs(rp->rrq_rx_id), ntohs(rp->rrq_ox_id));
	if (ep->oxid != ntohs(rp->rrq_ox_id))
		goto unlock_reject;
	if (ep->rxid != ntohs(rp->rrq_rx_id) &&
	    ep->rxid != FC_XID_UNKNOWN)
		goto unlock_reject;
	explan = ELS_EXPL_SID;
	if (ep->sid != sid)
		goto unlock_reject;

	/*
	 * Clear Recovery Qualifier state, and cancel timer if complete.
	 */
	if (ep->esb_stat & ESB_ST_REC_QUAL) {
		ep->esb_stat &= ~ESB_ST_REC_QUAL;
		atomic_dec(&ep->ex_refcnt);	/* drop hold for rec qual */
	}
	if (ep->esb_stat & ESB_ST_COMPLETE)
		fc_exch_timer_cancel(ep);

	spin_unlock_bh(&ep->ex_lock);

	/*
	 * Send LS_ACC.
	 */
	fc_seq_ls_acc(fp);
	goto out;

unlock_reject:
	spin_unlock_bh(&ep->ex_lock);
reject:
	fc_seq_ls_rjt(fp, ELS_RJT_LOGIC, explan);
out:
	if (ep)
		fc_exch_release(ep);	/* drop hold from fc_exch_find */
}