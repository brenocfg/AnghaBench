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
struct si476x_core {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  si476x_core_get_and_signal_status (struct si476x_core*) ; 

__attribute__((used)) static irqreturn_t si476x_core_interrupt(int irq, void *dev)
{
	struct si476x_core *core = dev;

	si476x_core_get_and_signal_status(core);

	return IRQ_HANDLED;
}