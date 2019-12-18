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
struct m5mols_info {int /*<<< orphan*/  irq_waitq; int /*<<< orphan*/  irq_done; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct m5mols_info* to_m5mols (void*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t m5mols_irq_handler(int irq, void *data)
{
	struct m5mols_info *info = to_m5mols(data);

	atomic_set(&info->irq_done, 1);
	wake_up_interruptible(&info->irq_waitq);

	return IRQ_HANDLED;
}