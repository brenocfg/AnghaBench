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
struct irq_chip {int /*<<< orphan*/  (* irq_eoi ) (int /*<<< orphan*/ ) ;} ;
struct dwapb_gpio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwapb_do_irq (struct dwapb_gpio*) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct dwapb_gpio* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_desc_get_irq_data (struct irq_desc*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwapb_irq_handler(struct irq_desc *desc)
{
	struct dwapb_gpio *gpio = irq_desc_get_handler_data(desc);
	struct irq_chip *chip = irq_desc_get_chip(desc);

	dwapb_do_irq(gpio);

	if (chip->irq_eoi)
		chip->irq_eoi(irq_desc_get_irq_data(desc));
}