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
struct subchannel {int /*<<< orphan*/  lock; } ;
struct eadm_private {scalar_t__ state; int /*<<< orphan*/ * completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 scalar_t__ EADM_BUSY ; 
 int EBUSY ; 
 int cio_disable_subchannel (struct subchannel*) ; 
 int /*<<< orphan*/  completion ; 
 scalar_t__ eadm_subchannel_clear (struct subchannel*) ; 
 int /*<<< orphan*/  eadm_subchannel_set_timeout (struct subchannel*,int /*<<< orphan*/ ) ; 
 struct eadm_private* get_eadm_private (struct subchannel*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_io (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eadm_quiesce(struct subchannel *sch)
{
	struct eadm_private *private = get_eadm_private(sch);
	DECLARE_COMPLETION_ONSTACK(completion);
	int ret;

	spin_lock_irq(sch->lock);
	if (private->state != EADM_BUSY)
		goto disable;

	if (eadm_subchannel_clear(sch))
		goto disable;

	private->completion = &completion;
	spin_unlock_irq(sch->lock);

	wait_for_completion_io(&completion);

	spin_lock_irq(sch->lock);
	private->completion = NULL;

disable:
	eadm_subchannel_set_timeout(sch, 0);
	do {
		ret = cio_disable_subchannel(sch);
	} while (ret == -EBUSY);

	spin_unlock_irq(sch->lock);
}