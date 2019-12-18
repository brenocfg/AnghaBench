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
struct TYPE_2__ {int /*<<< orphan*/  ioc; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; TYPE_1__ bfa; } ;
struct bfa_bsg_gen_s {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 unsigned int IOCMD_IOC_RESET_FWSTATS ; 
 unsigned int IOCMD_IOC_RESET_STATS ; 
 int /*<<< orphan*/  bfa_ioc_clear_stats (TYPE_1__*) ; 
 int /*<<< orphan*/  bfa_ioc_fw_stats_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_ioc_reset_stats(struct bfad_s *bfad, void *cmd, unsigned int v_cmd)
{
	struct bfa_bsg_gen_s *iocmd = (struct bfa_bsg_gen_s *)cmd;
	unsigned long	flags;

	if (v_cmd == IOCMD_IOC_RESET_STATS) {
		bfa_ioc_clear_stats(&bfad->bfa);
		iocmd->status = BFA_STATUS_OK;
	} else if (v_cmd == IOCMD_IOC_RESET_FWSTATS) {
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		iocmd->status = bfa_ioc_fw_stats_clear(&bfad->bfa.ioc);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	}

	return 0;
}