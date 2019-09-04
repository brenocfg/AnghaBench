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
struct IsdnCardState {scalar_t__ (* irq_func ) (int,struct IsdnCardState*) ;int /*<<< orphan*/  irq_cnt; } ;
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ stub1 (int,struct IsdnCardState*) ; 

__attribute__((used)) static irqreturn_t card_irq(int intno, void *dev_id)
{
	struct IsdnCardState *cs = dev_id;
	irqreturn_t ret = cs->irq_func(intno, cs);

	if (ret == IRQ_HANDLED)
		cs->irq_cnt++;
	return ret;
}