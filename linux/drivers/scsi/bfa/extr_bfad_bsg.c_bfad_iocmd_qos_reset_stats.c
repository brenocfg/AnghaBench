#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ioc; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; TYPE_2__ bfa; } ;
struct bfad_hal_comp {scalar_t__ status; int /*<<< orphan*/  comp; } ;
struct TYPE_4__ {scalar_t__ topology; } ;
struct bfa_fcport_s {scalar_t__ topology; TYPE_1__ cfg; } ;
struct bfa_cb_pending_q_s {int dummy; } ;
struct bfa_bsg_gen_s {scalar_t__ status; } ;
typedef  int /*<<< orphan*/  bfa_cb_cbfn_t ;

/* Variables and functions */
 struct bfa_fcport_s* BFA_FCPORT_MOD (TYPE_2__*) ; 
 scalar_t__ BFA_PORT_TOPOLOGY_LOOP ; 
 scalar_t__ BFA_STATUS_OK ; 
 scalar_t__ BFA_STATUS_TOPOLOGY_LOOP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ bfa_fcport_clear_stats (TYPE_2__*,struct bfa_cb_pending_q_s*) ; 
 int /*<<< orphan*/  bfa_ioc_get_fcmode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_pending_q_init (struct bfa_cb_pending_q_s*,int /*<<< orphan*/ ,struct bfad_hal_comp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,scalar_t__) ; 
 scalar_t__ bfad_hcb_comp ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
bfad_iocmd_qos_reset_stats(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_gen_s *iocmd = (struct bfa_bsg_gen_s *)cmd;
	struct bfad_hal_comp fcomp;
	unsigned long	flags;
	struct bfa_cb_pending_q_s cb_qe;
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);

	init_completion(&fcomp.comp);
	bfa_pending_q_init(&cb_qe, (bfa_cb_cbfn_t)bfad_hcb_comp,
			   &fcomp, NULL);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	WARN_ON(!bfa_ioc_get_fcmode(&bfad->bfa.ioc));
	if ((fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP) &&
		(fcport->topology == BFA_PORT_TOPOLOGY_LOOP))
		iocmd->status = BFA_STATUS_TOPOLOGY_LOOP;
	else
		iocmd->status = bfa_fcport_clear_stats(&bfad->bfa, &cb_qe);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	if (iocmd->status != BFA_STATUS_OK) {
		bfa_trc(bfad, iocmd->status);
		goto out;
	}
	wait_for_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	return 0;
}