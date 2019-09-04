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
struct octeon_mbox_cmd {int dummy; } ;
struct octeon_mbox {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  mbox_read_reg; struct octeon_mbox_cmd mbox_resp; } ;
struct octeon_device {struct octeon_mbox** mbox; } ;

/* Variables and functions */
 int OCTEON_MBOX_STATE_IDLE ; 
 int OCTEON_MBOX_STATE_RESPONSE_PENDING ; 
 int /*<<< orphan*/  OCTEON_PFVFSIG ; 
 int /*<<< orphan*/  memset (struct octeon_mbox_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int octeon_mbox_cancel(struct octeon_device *oct, int q_no)
{
	struct octeon_mbox *mbox = oct->mbox[q_no];
	struct octeon_mbox_cmd *mbox_cmd;
	unsigned long flags = 0;

	spin_lock_irqsave(&mbox->lock, flags);
	mbox_cmd = &mbox->mbox_resp;

	if (!(mbox->state & OCTEON_MBOX_STATE_RESPONSE_PENDING)) {
		spin_unlock_irqrestore(&mbox->lock, flags);
		return 1;
	}

	mbox->state = OCTEON_MBOX_STATE_IDLE;
	memset(mbox_cmd, 0, sizeof(*mbox_cmd));
	writeq(OCTEON_PFVFSIG, mbox->mbox_read_reg);
	spin_unlock_irqrestore(&mbox->lock, flags);

	return 0;
}