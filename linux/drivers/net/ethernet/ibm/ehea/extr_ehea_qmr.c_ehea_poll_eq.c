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
struct ehea_eqe {int dummy; } ;
struct ehea_eq {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  hw_queue; } ;

/* Variables and functions */
 struct ehea_eqe* hw_eqit_eq_get_inc_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct ehea_eqe *ehea_poll_eq(struct ehea_eq *eq)
{
	struct ehea_eqe *eqe;
	unsigned long flags;

	spin_lock_irqsave(&eq->spinlock, flags);
	eqe = hw_eqit_eq_get_inc_valid(&eq->hw_queue);
	spin_unlock_irqrestore(&eq->spinlock, flags);

	return eqe;
}