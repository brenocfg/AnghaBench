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
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa; } ;
struct bfad_hal_comp {scalar_t__ status; int /*<<< orphan*/  comp; } ;
struct bfa_bsg_sfp_media_s {scalar_t__ status; int /*<<< orphan*/  media; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_SFP_MOD (int /*<<< orphan*/ *) ; 
 scalar_t__ BFA_STATUS_SFP_NOT_READY ; 
 scalar_t__ bfa_sfp_media (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfad_hal_comp*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,scalar_t__) ; 
 int /*<<< orphan*/  bfad_hcb_comp ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
bfad_iocmd_sfp_media(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_sfp_media_s *iocmd = (struct bfa_bsg_sfp_media_s *)cmd;
	struct bfad_hal_comp	fcomp;
	unsigned long	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_sfp_media(BFA_SFP_MOD(&bfad->bfa), &iocmd->media,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	bfa_trc(bfad, iocmd->status);
	if (iocmd->status != BFA_STATUS_SFP_NOT_READY)
		goto out;

	wait_for_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	return 0;
}