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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nes_vnic {struct nes_device* nesdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct nes_qp {int term_flags; int /*<<< orphan*/  terminate_timer; int /*<<< orphan*/  lock; scalar_t__ hte_added; TYPE_1__ ibqp; } ;
struct nes_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_CQP_QP_DEL_HTE ; 
 int /*<<< orphan*/  NES_CQP_QP_IWARP_STATE_ERROR ; 
 int /*<<< orphan*/  NES_CQP_QP_RESET ; 
 int NES_TERM_DONE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nes_cm_disconn (struct nes_qp*) ; 
 int /*<<< orphan*/  nes_hw_modify_qp (struct nes_device*,struct nes_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct nes_vnic* to_nesvnic (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nes_terminate_done(struct nes_qp *nesqp, int timeout_occurred)
{
	u32 next_iwarp_state = NES_CQP_QP_IWARP_STATE_ERROR;
	unsigned long flags;
	struct nes_vnic *nesvnic = to_nesvnic(nesqp->ibqp.device);
	struct nes_device *nesdev = nesvnic->nesdev;
	u8 first_time = 0;

	spin_lock_irqsave(&nesqp->lock, flags);
	if (nesqp->hte_added) {
		nesqp->hte_added = 0;
		next_iwarp_state |= NES_CQP_QP_DEL_HTE;
	}

	first_time = (nesqp->term_flags & NES_TERM_DONE) == 0;
	nesqp->term_flags |= NES_TERM_DONE;
	spin_unlock_irqrestore(&nesqp->lock, flags);

	/* Make sure we go through this only once */
	if (first_time) {
		if (timeout_occurred == 0)
			del_timer(&nesqp->terminate_timer);
		else
			next_iwarp_state |= NES_CQP_QP_RESET;

		nes_hw_modify_qp(nesdev, nesqp, next_iwarp_state, 0, 0);
		nes_cm_disconn(nesqp);
	}
}