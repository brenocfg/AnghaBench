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
typedef  int /*<<< orphan*/  u32 ;
struct fc_lport {int /*<<< orphan*/  e_d_tov; int /*<<< orphan*/  port_id; } ;
struct fc_frame {int dummy; } ;
struct fc_exch {int esb_stat; int state; int /*<<< orphan*/  ex_lock; int /*<<< orphan*/  r_a_tov; int /*<<< orphan*/  sid; int /*<<< orphan*/  did; int /*<<< orphan*/  rxid; int /*<<< orphan*/  oxid; struct fc_lport* lp; } ;
struct fc_els_rrq {void* rrq_rx_id; void* rrq_ox_id; int /*<<< orphan*/  rrq_s_id; int /*<<< orphan*/  rrq_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_RRQ ; 
 int ESB_ST_REC_QUAL ; 
 int ESB_ST_RESP ; 
 int /*<<< orphan*/  FC_EXCH_DBG (struct fc_exch*,char*) ; 
 int FC_EX_DONE ; 
 int FC_EX_RST_CLEANUP ; 
 int FC_FC_END_SEQ ; 
 int FC_FC_FIRST_SEQ ; 
 int FC_FC_SEQ_INIT ; 
 int /*<<< orphan*/  FC_RCTL_ELS_REQ ; 
 int /*<<< orphan*/  FC_TYPE_ELS ; 
 int /*<<< orphan*/  fc_exch_release (struct fc_exch*) ; 
 int /*<<< orphan*/  fc_exch_rrq_resp ; 
 scalar_t__ fc_exch_seq_send (struct fc_lport*,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct fc_exch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_exch_timer_set_locked (struct fc_exch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_fill_fc_hdr (struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,int) ; 
 struct fc_els_rrq* fc_frame_payload_get (struct fc_frame*,int) ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fc_els_rrq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_exch_rrq(struct fc_exch *ep)
{
	struct fc_lport *lport;
	struct fc_els_rrq *rrq;
	struct fc_frame *fp;
	u32 did;

	lport = ep->lp;

	fp = fc_frame_alloc(lport, sizeof(*rrq));
	if (!fp)
		goto retry;

	rrq = fc_frame_payload_get(fp, sizeof(*rrq));
	memset(rrq, 0, sizeof(*rrq));
	rrq->rrq_cmd = ELS_RRQ;
	hton24(rrq->rrq_s_id, ep->sid);
	rrq->rrq_ox_id = htons(ep->oxid);
	rrq->rrq_rx_id = htons(ep->rxid);

	did = ep->did;
	if (ep->esb_stat & ESB_ST_RESP)
		did = ep->sid;

	fc_fill_fc_hdr(fp, FC_RCTL_ELS_REQ, did,
		       lport->port_id, FC_TYPE_ELS,
		       FC_FC_FIRST_SEQ | FC_FC_END_SEQ | FC_FC_SEQ_INIT, 0);

	if (fc_exch_seq_send(lport, fp, fc_exch_rrq_resp, NULL, ep,
			     lport->e_d_tov))
		return;

retry:
	FC_EXCH_DBG(ep, "exch: RRQ send failed\n");
	spin_lock_bh(&ep->ex_lock);
	if (ep->state & (FC_EX_RST_CLEANUP | FC_EX_DONE)) {
		spin_unlock_bh(&ep->ex_lock);
		/* drop hold for rec qual */
		fc_exch_release(ep);
		return;
	}
	ep->esb_stat |= ESB_ST_REC_QUAL;
	fc_exch_timer_set_locked(ep, ep->r_a_tov);
	spin_unlock_bh(&ep->ex_lock);
}