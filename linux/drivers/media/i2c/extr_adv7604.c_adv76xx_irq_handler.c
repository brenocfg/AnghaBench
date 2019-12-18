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
struct adv76xx_state {int /*<<< orphan*/  sd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  adv76xx_isr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static irqreturn_t adv76xx_irq_handler(int irq, void *dev_id)
{
	struct adv76xx_state *state = dev_id;
	bool handled = false;

	adv76xx_isr(&state->sd, 0, &handled);

	return handled ? IRQ_HANDLED : IRQ_NONE;
}