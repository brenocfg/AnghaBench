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
 int /*<<< orphan*/  irq_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4m_unmask_irq (struct irq_data*) ; 

__attribute__((used)) static unsigned int sun4m_startup_irq(struct irq_data *data)
{
	irq_link(data->irq);
	sun4m_unmask_irq(data);
	return 0;
}