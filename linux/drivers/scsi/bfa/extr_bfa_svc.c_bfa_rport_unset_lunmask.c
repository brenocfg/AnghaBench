#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wwn_t ;
struct bfa_s {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lp_tag; } ;
struct bfa_rport_s {int /*<<< orphan*/  lun_mask; TYPE_1__ rport_info; scalar_t__ rport_drv; } ;
struct bfa_lps_mod_s {int dummy; } ;
struct bfa_fcs_rport_s {int /*<<< orphan*/  pwwn; } ;
struct TYPE_4__ {int /*<<< orphan*/  lun_mask; int /*<<< orphan*/  pwwn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 TYPE_2__* BFA_LPS_FROM_TAG (struct bfa_lps_mod_s*,int /*<<< orphan*/ ) ; 
 struct bfa_lps_mod_s* BFA_LPS_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  BFA_LP_TAG_INVALID ; 
 int /*<<< orphan*/  BFA_RPORT_TAG_INVALID ; 
 int /*<<< orphan*/  bfa_fcpim_lunmask_rp_update (struct bfa_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_rport_unset_lunmask(struct bfa_s *bfa, struct bfa_rport_s *rp)
{
	struct bfa_lps_mod_s	*lps_mod = BFA_LPS_MOD(bfa);
	wwn_t	lp_wwn, rp_wwn;

	rp_wwn = ((struct bfa_fcs_rport_s *)rp->rport_drv)->pwwn;
	lp_wwn = (BFA_LPS_FROM_TAG(lps_mod, rp->rport_info.lp_tag))->pwwn;

	BFA_LPS_FROM_TAG(lps_mod, rp->rport_info.lp_tag)->lun_mask =
				rp->lun_mask = BFA_FALSE;
	bfa_fcpim_lunmask_rp_update(bfa, lp_wwn, rp_wwn,
			BFA_RPORT_TAG_INVALID, BFA_LP_TAG_INVALID);
}