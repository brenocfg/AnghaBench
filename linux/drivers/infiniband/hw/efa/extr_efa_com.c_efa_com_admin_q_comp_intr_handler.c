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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ cq; } ;
struct efa_com_dev {TYPE_2__ aq; } ;

/* Variables and functions */
 int /*<<< orphan*/  efa_com_handle_admin_completion (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void efa_com_admin_q_comp_intr_handler(struct efa_com_dev *edev)
{
	unsigned long flags;

	spin_lock_irqsave(&edev->aq.cq.lock, flags);
	efa_com_handle_admin_completion(&edev->aq);
	spin_unlock_irqrestore(&edev->aq.cq.lock, flags);
}