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
typedef  int /*<<< orphan*/  u16 ;
struct fc_seq {int dummy; } ;
struct fc_frame_header {int fh_r_ctl; int /*<<< orphan*/  fh_f_ctl; } ;
struct fc_frame {int dummy; } ;
struct fc_exch {int esb_stat; scalar_t__ fh_type; int /*<<< orphan*/  r_a_tov; int /*<<< orphan*/  ex_lock; struct fc_seq seq; int /*<<< orphan*/  seq_id; int /*<<< orphan*/  timeout_work; } ;
struct fc_ba_acc {int /*<<< orphan*/  ba_seq_id; int /*<<< orphan*/  ba_seq_id_val; int /*<<< orphan*/  ba_high_seq_cnt; int /*<<< orphan*/  ba_low_seq_cnt; } ;

/* Variables and functions */
 int ESB_ST_REC_QUAL ; 
 int /*<<< orphan*/  FC_BA_SEQ_ID_VAL ; 
 int /*<<< orphan*/  FC_EXCH_DBG (struct fc_exch*,char*,...) ; 
 int FC_FC_LAST_SEQ ; 
#define  FC_RCTL_BA_ACC 129 
#define  FC_RCTL_BA_RJT 128 
 scalar_t__ FC_TYPE_FCP ; 
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_exch_delete (struct fc_exch*) ; 
 int fc_exch_done_locked (struct fc_exch*) ; 
 int /*<<< orphan*/  fc_exch_hold (struct fc_exch*) ; 
 int /*<<< orphan*/  fc_exch_rctl_name (int) ; 
 int /*<<< orphan*/  fc_exch_release (struct fc_exch*) ; 
 int /*<<< orphan*/  fc_exch_timer_set (struct fc_exch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 struct fc_ba_acc* fc_frame_payload_get (struct fc_frame*,int) ; 
 int /*<<< orphan*/  fc_invoke_resp (struct fc_exch*,struct fc_seq*,struct fc_frame*) ; 
 int ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_exch_abts_resp(struct fc_exch *ep, struct fc_frame *fp)
{
	struct fc_frame_header *fh;
	struct fc_ba_acc *ap;
	struct fc_seq *sp;
	u16 low;
	u16 high;
	int rc = 1, has_rec = 0;

	fh = fc_frame_header_get(fp);
	FC_EXCH_DBG(ep, "exch: BLS rctl %x - %s\n", fh->fh_r_ctl,
		    fc_exch_rctl_name(fh->fh_r_ctl));

	if (cancel_delayed_work_sync(&ep->timeout_work)) {
		FC_EXCH_DBG(ep, "Exchange timer canceled due to ABTS response\n");
		fc_exch_release(ep);	/* release from pending timer hold */
	}

	spin_lock_bh(&ep->ex_lock);
	switch (fh->fh_r_ctl) {
	case FC_RCTL_BA_ACC:
		ap = fc_frame_payload_get(fp, sizeof(*ap));
		if (!ap)
			break;

		/*
		 * Decide whether to establish a Recovery Qualifier.
		 * We do this if there is a non-empty SEQ_CNT range and
		 * SEQ_ID is the same as the one we aborted.
		 */
		low = ntohs(ap->ba_low_seq_cnt);
		high = ntohs(ap->ba_high_seq_cnt);
		if ((ep->esb_stat & ESB_ST_REC_QUAL) == 0 &&
		    (ap->ba_seq_id_val != FC_BA_SEQ_ID_VAL ||
		     ap->ba_seq_id == ep->seq_id) && low != high) {
			ep->esb_stat |= ESB_ST_REC_QUAL;
			fc_exch_hold(ep);  /* hold for recovery qualifier */
			has_rec = 1;
		}
		break;
	case FC_RCTL_BA_RJT:
		break;
	default:
		break;
	}

	/* do we need to do some other checks here. Can we reuse more of
	 * fc_exch_recv_seq_resp
	 */
	sp = &ep->seq;
	/*
	 * do we want to check END_SEQ as well as LAST_SEQ here?
	 */
	if (ep->fh_type != FC_TYPE_FCP &&
	    ntoh24(fh->fh_f_ctl) & FC_FC_LAST_SEQ)
		rc = fc_exch_done_locked(ep);
	spin_unlock_bh(&ep->ex_lock);

	fc_exch_hold(ep);
	if (!rc)
		fc_exch_delete(ep);
	if (!fc_invoke_resp(ep, sp, fp))
		fc_frame_free(fp);
	if (has_rec)
		fc_exch_timer_set(ep, ep->r_a_tov);
	fc_exch_release(ep);
}