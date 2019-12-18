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
struct bfa_bsg_fcpim_profile_s {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 unsigned int IOCMD_FCPIM_PROFILE_OFF ; 
 unsigned int IOCMD_FCPIM_PROFILE_ON ; 
 int /*<<< orphan*/  bfa_fcpim_profile_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcpim_profile_on (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_fcpim_cfg_profile(struct bfad_s *bfad, void *cmd, unsigned int v_cmd)
{
	struct bfa_bsg_fcpim_profile_s *iocmd =
				(struct bfa_bsg_fcpim_profile_s *)cmd;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	if (v_cmd == IOCMD_FCPIM_PROFILE_ON)
		iocmd->status = bfa_fcpim_profile_on(&bfad->bfa, ktime_get_real_seconds());
	else if (v_cmd == IOCMD_FCPIM_PROFILE_OFF)
		iocmd->status = bfa_fcpim_profile_off(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	return 0;
}