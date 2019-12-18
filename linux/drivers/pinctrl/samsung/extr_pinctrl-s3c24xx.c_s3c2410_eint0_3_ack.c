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
struct samsung_pin_bank {TYPE_1__* irq_domain; } ;
struct s3c24xx_eint_domain_data {struct s3c24xx_eint_data* eint_data; } ;
struct s3c24xx_eint_data {int* parents; } ;
struct irq_data {size_t hwirq; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_ack ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {struct s3c24xx_eint_domain_data* host_data; } ;

/* Variables and functions */
 struct samsung_pin_bank* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct irq_chip* irq_get_chip (int) ; 
 int /*<<< orphan*/  irq_get_irq_data (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c2410_eint0_3_ack(struct irq_data *data)
{
	struct samsung_pin_bank *bank = irq_data_get_irq_chip_data(data);
	struct s3c24xx_eint_domain_data *ddata = bank->irq_domain->host_data;
	struct s3c24xx_eint_data *eint_data = ddata->eint_data;
	int parent_irq = eint_data->parents[data->hwirq];
	struct irq_chip *parent_chip = irq_get_chip(parent_irq);

	parent_chip->irq_ack(irq_get_irq_data(parent_irq));
}