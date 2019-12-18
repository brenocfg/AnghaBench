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
typedef  int u32 ;
struct gfar_priv_grp {TYPE_1__* regs; int /*<<< orphan*/  napi_rx; int /*<<< orphan*/  grplock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  ievent; int /*<<< orphan*/  imask; } ;

/* Variables and functions */
 int IEVENT_FGPI ; 
 int IEVENT_RX_MASK ; 
 int IMASK_RX_DISABLED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int gfar_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfar_write (int /*<<< orphan*/ *,int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t gfar_receive(int irq, void *grp_id)
{
	struct gfar_priv_grp *grp = (struct gfar_priv_grp *)grp_id;
	unsigned long flags;
	u32 imask, ievent;

	ievent = gfar_read(&grp->regs->ievent);

	if (unlikely(ievent & IEVENT_FGPI)) {
		gfar_write(&grp->regs->ievent, IEVENT_FGPI);
		return IRQ_HANDLED;
	}

	if (likely(napi_schedule_prep(&grp->napi_rx))) {
		spin_lock_irqsave(&grp->grplock, flags);
		imask = gfar_read(&grp->regs->imask);
		imask &= IMASK_RX_DISABLED;
		gfar_write(&grp->regs->imask, imask);
		spin_unlock_irqrestore(&grp->grplock, flags);
		__napi_schedule(&grp->napi_rx);
	} else {
		/* Clear IEVENT, so interrupts aren't called again
		 * because of the packets that have already arrived.
		 */
		gfar_write(&grp->regs->ievent, IEVENT_RX_MASK);
	}

	return IRQ_HANDLED;
}