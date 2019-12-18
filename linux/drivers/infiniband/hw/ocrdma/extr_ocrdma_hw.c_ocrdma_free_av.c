#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct ocrdma_dev {TYPE_2__ av_tbl; } ;
struct ocrdma_ah {TYPE_1__* av; } ;
struct TYPE_3__ {scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ocrdma_free_av(struct ocrdma_dev *dev, struct ocrdma_ah *ah)
{
	unsigned long flags;
	spin_lock_irqsave(&dev->av_tbl.lock, flags);
	ah->av->valid = 0;
	spin_unlock_irqrestore(&dev->av_tbl.lock, flags);
}