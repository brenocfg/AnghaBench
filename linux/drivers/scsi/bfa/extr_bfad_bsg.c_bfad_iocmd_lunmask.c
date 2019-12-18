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
struct bfa_bsg_gen_s {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 scalar_t__ BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 unsigned int IOCMD_FCPIM_LUNMASK_CLEAR ; 
 unsigned int IOCMD_FCPIM_LUNMASK_DISABLE ; 
 unsigned int IOCMD_FCPIM_LUNMASK_ENABLE ; 
 scalar_t__ bfa_fcpim_lunmask_clear (int /*<<< orphan*/ *) ; 
 void* bfa_fcpim_lunmask_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfad_iocmd_lunmask_reset_lunscan_mode (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_lunmask(struct bfad_s *bfad, void *pcmd, unsigned int v_cmd)
{
	struct bfa_bsg_gen_s *iocmd = (struct bfa_bsg_gen_s *)pcmd;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	if (v_cmd == IOCMD_FCPIM_LUNMASK_ENABLE) {
		iocmd->status = bfa_fcpim_lunmask_update(&bfad->bfa, BFA_TRUE);
		/* Set the LUN Scanning mode to be Sequential scan */
		if (iocmd->status == BFA_STATUS_OK)
			bfad_iocmd_lunmask_reset_lunscan_mode(bfad, BFA_TRUE);
	} else if (v_cmd == IOCMD_FCPIM_LUNMASK_DISABLE) {
		iocmd->status = bfa_fcpim_lunmask_update(&bfad->bfa, BFA_FALSE);
		/* Set the LUN Scanning mode to default REPORT_LUNS scan */
		if (iocmd->status == BFA_STATUS_OK)
			bfad_iocmd_lunmask_reset_lunscan_mode(bfad, BFA_FALSE);
	} else if (v_cmd == IOCMD_FCPIM_LUNMASK_CLEAR)
		iocmd->status = bfa_fcpim_lunmask_clear(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	return 0;
}