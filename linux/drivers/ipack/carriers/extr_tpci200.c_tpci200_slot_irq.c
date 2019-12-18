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
struct slot_irq {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tpci200_slot_irq(struct slot_irq *slot_irq)
{
	irqreturn_t ret;

	if (!slot_irq)
		return -ENODEV;
	ret = slot_irq->handler(slot_irq->arg);

	return ret;
}