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
struct bfa_ioc_mbox_mod_s {TYPE_1__* mbhdlr; int /*<<< orphan*/  cmd_q; } ;
struct bfa_ioc_s {int /*<<< orphan*/  bfa; struct bfa_ioc_mbox_mod_s mbox_mod; } ;
struct TYPE_2__ {int /*<<< orphan*/  cbarg; int /*<<< orphan*/ * cbfn; } ;

/* Variables and functions */
 int BFI_MC_MAX ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_ioc_mbox_attach(struct bfa_ioc_s *ioc)
{
	struct bfa_ioc_mbox_mod_s	*mod = &ioc->mbox_mod;
	int	mc;

	INIT_LIST_HEAD(&mod->cmd_q);
	for (mc = 0; mc < BFI_MC_MAX; mc++) {
		mod->mbhdlr[mc].cbfn = NULL;
		mod->mbhdlr[mc].cbarg = ioc->bfa;
	}
}