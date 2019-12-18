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
struct mt6397_chip {int /*<<< orphan*/ * int_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  mt6397_irq_handle_reg (struct mt6397_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t mt6397_irq_thread(int irq, void *data)
{
	struct mt6397_chip *mt6397 = data;

	mt6397_irq_handle_reg(mt6397, mt6397->int_status[0], 0);
	mt6397_irq_handle_reg(mt6397, mt6397->int_status[1], 16);

	return IRQ_HANDLED;
}