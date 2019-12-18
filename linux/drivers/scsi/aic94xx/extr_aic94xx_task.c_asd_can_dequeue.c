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
struct TYPE_2__ {int can_queue; int /*<<< orphan*/  pend_q_lock; } ;
struct asd_ha_struct {TYPE_1__ seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void asd_can_dequeue(struct asd_ha_struct *asd_ha, int num)
{
	unsigned long flags;

	spin_lock_irqsave(&asd_ha->seq.pend_q_lock, flags);
	asd_ha->seq.can_queue += num;
	spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);
}