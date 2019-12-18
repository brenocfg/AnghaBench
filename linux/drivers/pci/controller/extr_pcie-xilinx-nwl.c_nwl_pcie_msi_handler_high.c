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
struct nwl_pcie {int dummy; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGF_MSI_STATUS_HI ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct nwl_pcie* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  nwl_pcie_handle_msi_irq (struct nwl_pcie*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nwl_pcie_msi_handler_high(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct nwl_pcie *pcie = irq_desc_get_handler_data(desc);

	chained_irq_enter(chip, desc);
	nwl_pcie_handle_msi_irq(pcie, MSGF_MSI_STATUS_HI);
	chained_irq_exit(chip, desc);
}