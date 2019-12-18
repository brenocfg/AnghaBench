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
struct bfa_bsg_bbcr_attr_s {int /*<<< orphan*/  attr; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcport_get_bbcr_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_port_get_bbcr_attr(struct bfad_s *bfad, void *pcmd)
{
	struct bfa_bsg_bbcr_attr_s *iocmd = (struct bfa_bsg_bbcr_attr_s *) pcmd;
	unsigned long flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status =
		bfa_fcport_get_bbcr_attr(&bfad->bfa, &iocmd->attr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	return 0;
}