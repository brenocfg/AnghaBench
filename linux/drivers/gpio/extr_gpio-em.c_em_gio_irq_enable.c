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
struct irq_data {int dummy; } ;
struct em_gio_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIO_IEN ; 
 int /*<<< orphan*/  em_gio_write (struct em_gio_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct em_gio_priv* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static void em_gio_irq_enable(struct irq_data *d)
{
	struct em_gio_priv *p = irq_data_get_irq_chip_data(d);

	em_gio_write(p, GIO_IEN, BIT(irqd_to_hwirq(d)));
}