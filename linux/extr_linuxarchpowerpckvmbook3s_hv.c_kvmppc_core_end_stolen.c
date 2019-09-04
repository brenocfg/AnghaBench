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
struct kvmppc_vcore {scalar_t__ preempt_tb; int /*<<< orphan*/  stoltb_lock; int /*<<< orphan*/  stolen_tb; } ;

/* Variables and functions */
 scalar_t__ TB_NIL ; 
 scalar_t__ mftb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void kvmppc_core_end_stolen(struct kvmppc_vcore *vc)
{
	unsigned long flags;

	spin_lock_irqsave(&vc->stoltb_lock, flags);
	if (vc->preempt_tb != TB_NIL) {
		vc->stolen_tb += mftb() - vc->preempt_tb;
		vc->preempt_tb = TB_NIL;
	}
	spin_unlock_irqrestore(&vc->stoltb_lock, flags);
}