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
typedef  size_t u16 ;
struct pasid_state {int /*<<< orphan*/  lock; TYPE_1__* pri; } ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void set_pri_tag_status(struct pasid_state *pasid_state,
			       u16 tag, int status)
{
	unsigned long flags;

	spin_lock_irqsave(&pasid_state->lock, flags);
	pasid_state->pri[tag].status = status;
	spin_unlock_irqrestore(&pasid_state->lock, flags);
}