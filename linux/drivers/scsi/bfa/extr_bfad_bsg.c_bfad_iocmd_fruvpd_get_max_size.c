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
struct bfa_bsg_fruvpd_max_size_s {int /*<<< orphan*/  max_size; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FRU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fruvpd_get_max_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_fruvpd_get_max_size(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_fruvpd_max_size_s *iocmd =
			(struct bfa_bsg_fruvpd_max_size_s *)cmd;
	unsigned long flags = 0;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fruvpd_get_max_size(BFA_FRU(&bfad->bfa),
						&iocmd->max_size);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	return 0;
}