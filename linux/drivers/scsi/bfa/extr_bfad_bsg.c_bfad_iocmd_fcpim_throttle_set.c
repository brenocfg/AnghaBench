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
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa; } ;
struct TYPE_2__ {int /*<<< orphan*/  cfg_value; } ;
struct bfa_bsg_fcpim_throttle_s {TYPE_1__ throttle; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcpim_throttle_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_fcpim_throttle_set(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_fcpim_throttle_s *iocmd =
			(struct bfa_bsg_fcpim_throttle_s *)cmd;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcpim_throttle_set(&bfad->bfa,
				iocmd->throttle.cfg_value);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	return 0;
}