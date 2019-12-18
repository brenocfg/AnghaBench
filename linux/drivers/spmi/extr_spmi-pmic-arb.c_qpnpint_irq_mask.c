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
typedef  int /*<<< orphan*/  u8 ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QPNPINT_REG_EN_CLR ; 
 int /*<<< orphan*/  hwirq_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qpnpint_spmi_write (struct irq_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void qpnpint_irq_mask(struct irq_data *d)
{
	u8 irq = hwirq_to_irq(d->hwirq);
	u8 data = BIT(irq);

	qpnpint_spmi_write(d, QPNPINT_REG_EN_CLR, &data, 1);
}