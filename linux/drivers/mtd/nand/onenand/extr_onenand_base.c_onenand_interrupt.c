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
struct TYPE_2__ {int /*<<< orphan*/  done; } ;
struct onenand_chip {TYPE_1__ complete; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t onenand_interrupt(int irq, void *data)
{
	struct onenand_chip *this = data;

	/* To handle shared interrupt */
	if (!this->complete.done)
		complete(&this->complete);

	return IRQ_HANDLED;
}