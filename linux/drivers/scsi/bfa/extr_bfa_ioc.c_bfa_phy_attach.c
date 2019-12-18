#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_trc_mod_s {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  qe; } ;
struct bfa_phy_s {scalar_t__ dbuf_pa; int /*<<< orphan*/ * dbuf_kva; struct bfa_ioc_s* ioc; TYPE_1__ ioc_notify; scalar_t__ op_busy; int /*<<< orphan*/ * cbarg; int /*<<< orphan*/ * cbfn; struct bfa_trc_mod_s* trcmod; } ;
struct bfa_ioc_s {int /*<<< orphan*/  notify_q; } ;
typedef  scalar_t__ bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_MC_PHY ; 
 int /*<<< orphan*/  bfa_ioc_mbox_regisr (struct bfa_ioc_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfa_phy_s*) ; 
 int /*<<< orphan*/  bfa_ioc_notify_init (TYPE_1__*,int /*<<< orphan*/ ,struct bfa_phy_s*) ; 
 int /*<<< orphan*/  bfa_phy_intr ; 
 int /*<<< orphan*/  bfa_phy_notify ; 
 int /*<<< orphan*/  bfa_q_qe_init (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bfa_phy_attach(struct bfa_phy_s *phy, struct bfa_ioc_s *ioc, void *dev,
		struct bfa_trc_mod_s *trcmod, bfa_boolean_t mincfg)
{
	phy->ioc = ioc;
	phy->trcmod = trcmod;
	phy->cbfn = NULL;
	phy->cbarg = NULL;
	phy->op_busy = 0;

	bfa_ioc_mbox_regisr(phy->ioc, BFI_MC_PHY, bfa_phy_intr, phy);
	bfa_q_qe_init(&phy->ioc_notify);
	bfa_ioc_notify_init(&phy->ioc_notify, bfa_phy_notify, phy);
	list_add_tail(&phy->ioc_notify.qe, &phy->ioc->notify_q);

	/* min driver doesn't need phy */
	if (mincfg) {
		phy->dbuf_kva = NULL;
		phy->dbuf_pa = 0;
	}
}