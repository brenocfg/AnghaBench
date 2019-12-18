#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct fc_rport_libfc_priv {int flags; } ;
struct fc_rport {struct fc_rport_libfc_priv* dd_data; } ;
struct TYPE_6__ {void (* function ) (struct timer_list*) ;} ;
struct TYPE_4__ {scalar_t__ fc_tm_flags; } ;
struct fc_fcp_pkt {int state; int /*<<< orphan*/  timer_delay; TYPE_3__ timer; TYPE_2__* lp; TYPE_1__ cdb_cmd; struct fc_rport* rport; } ;
struct TYPE_5__ {scalar_t__ qfull; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_FCP_DBG (struct fc_fcp_pkt*,char*,int /*<<< orphan*/ ,...) ; 
 int FC_RP_FLAGS_REC_SUPPORTED ; 
 int FC_SRB_FCP_PROCESSING_TMO ; 
 int FC_SRB_RCV_STATUS ; 
 int /*<<< orphan*/  FC_TIMED_OUT ; 
 int /*<<< orphan*/  fc_fcp_complete_locked (struct fc_fcp_pkt*) ; 
 scalar_t__ fc_fcp_lock_pkt (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_fcp_rec (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_fcp_recovery (struct fc_fcp_pkt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_fcp_timer_set (struct fc_fcp_pkt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_fcp_unlock_pkt (struct fc_fcp_pkt*) ; 
 struct fc_fcp_pkt* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct fc_fcp_pkt* fsp ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void fc_fcp_timeout(struct timer_list *t)
{
	struct fc_fcp_pkt *fsp = from_timer(fsp, t, timer);
	struct fc_rport *rport = fsp->rport;
	struct fc_rport_libfc_priv *rpriv = rport->dd_data;

	if (fc_fcp_lock_pkt(fsp))
		return;

	if (fsp->cdb_cmd.fc_tm_flags)
		goto unlock;

	if (fsp->lp->qfull) {
		FC_FCP_DBG(fsp, "fcp timeout, resetting timer delay %d\n",
			   fsp->timer_delay);
		fsp->timer.function = fc_fcp_timeout;
		fc_fcp_timer_set(fsp, fsp->timer_delay);
		goto unlock;
	}
	FC_FCP_DBG(fsp, "fcp timeout, delay %d flags %x state %x\n",
		   fsp->timer_delay, rpriv->flags, fsp->state);
	fsp->state |= FC_SRB_FCP_PROCESSING_TMO;

	if (rpriv->flags & FC_RP_FLAGS_REC_SUPPORTED)
		fc_fcp_rec(fsp);
	else if (fsp->state & FC_SRB_RCV_STATUS)
		fc_fcp_complete_locked(fsp);
	else
		fc_fcp_recovery(fsp, FC_TIMED_OUT);
	fsp->state &= ~FC_SRB_FCP_PROCESSING_TMO;
unlock:
	fc_fcp_unlock_pkt(fsp);
}