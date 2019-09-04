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
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSYSINT1REG ; 
 int SYSINT1_IRQ_TO_PIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icu1_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enable_sysint1_irq(struct irq_data *d)
{
	icu1_set(MSYSINT1REG, 1 << SYSINT1_IRQ_TO_PIN(d->irq));
}