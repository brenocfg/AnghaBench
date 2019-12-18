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
typedef  int /*<<< orphan*/  u32 ;
struct bnad_iocmd_comp {scalar_t__ comp_status; int /*<<< orphan*/  comp; struct bnad* bnad; } ;
struct bnad_drvinfo {scalar_t__ flash_status; int /*<<< orphan*/  flash_attr; scalar_t__ cee_status; int /*<<< orphan*/  cee_attr; int /*<<< orphan*/  ioc_attr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ioc; } ;
struct TYPE_4__ {int /*<<< orphan*/  flash; int /*<<< orphan*/  cee; TYPE_1__ ioceth; } ;
struct bnad {int /*<<< orphan*/  bna_lock; TYPE_2__ bna; } ;

/* Variables and functions */
 int BFA_STATUS_FAILED ; 
 int BFA_STATUS_OK ; 
 int bfa_nw_cee_get_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bnad_iocmd_comp*) ; 
 int bfa_nw_flash_get_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bnad_iocmd_comp*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_get_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnad_cb_completion ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bnad_get_debug_drvinfo(struct bnad *bnad, void *buffer, u32 len)
{
	struct bnad_drvinfo *drvinfo = (struct bnad_drvinfo *) buffer;
	struct bnad_iocmd_comp fcomp;
	unsigned long flags = 0;
	int ret = BFA_STATUS_FAILED;

	/* Get IOC info */
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bfa_nw_ioc_get_attr(&bnad->bna.ioceth.ioc, &drvinfo->ioc_attr);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	/* Retrieve CEE related info */
	fcomp.bnad = bnad;
	fcomp.comp_status = 0;
	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	ret = bfa_nw_cee_get_attr(&bnad->bna.cee, &drvinfo->cee_attr,
				bnad_cb_completion, &fcomp);
	if (ret != BFA_STATUS_OK) {
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		goto out;
	}
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	wait_for_completion(&fcomp.comp);
	drvinfo->cee_status = fcomp.comp_status;

	/* Retrieve flash partition info */
	fcomp.comp_status = 0;
	reinit_completion(&fcomp.comp);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	ret = bfa_nw_flash_get_attr(&bnad->bna.flash, &drvinfo->flash_attr,
				bnad_cb_completion, &fcomp);
	if (ret != BFA_STATUS_OK) {
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		goto out;
	}
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	wait_for_completion(&fcomp.comp);
	drvinfo->flash_status = fcomp.comp_status;
out:
	return ret;
}