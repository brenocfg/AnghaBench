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
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
struct ipu_soc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  ipu_irq_handle (struct ipu_soc*,int const*,int /*<<< orphan*/ ) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct ipu_soc* irq_desc_get_handler_data (struct irq_desc*) ; 

__attribute__((used)) static void ipu_irq_handler(struct irq_desc *desc)
{
	struct ipu_soc *ipu = irq_desc_get_handler_data(desc);
	struct irq_chip *chip = irq_desc_get_chip(desc);
	static const int int_reg[] = { 0, 1, 2, 3, 10, 11, 12, 13, 14};

	chained_irq_enter(chip, desc);

	ipu_irq_handle(ipu, int_reg, ARRAY_SIZE(int_reg));

	chained_irq_exit(chip, desc);
}